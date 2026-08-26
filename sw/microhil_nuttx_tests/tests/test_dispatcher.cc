#include "gtest/gtest.h"
#include "mocks/mocks.h"
extern "C" {
#include "command/microhil_dispatcher.h"
}
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <stdexcept>

class StdoutCapture {
public:
    StdoutCapture() {
        fflush(stdout);
        old_stdout = dup(fileno(stdout));
        if (pipe(pipe_fds) == 0) {
            dup2(pipe_fds[1], fileno(stdout));
            close(pipe_fds[1]);
        }
    }
    std::string GetCapture() {
        fflush(stdout);
        dup2(old_stdout, fileno(stdout));
        close(old_stdout);
        
        std::string out;
        char buf[1024];
        ssize_t bytes_read;
        int flags = fcntl(pipe_fds[0], F_GETFL, 0);
        fcntl(pipe_fds[0], F_SETFL, flags | O_NONBLOCK);
        while ((bytes_read = read(pipe_fds[0], buf, sizeof(buf) - 1)) > 0) {
            buf[bytes_read] = '\0';
            out += buf;
        }
        close(pipe_fds[0]);
        return out;
    }
private:
    int old_stdout;
    int pipe_fds[2];
};

class DispatcherTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_relay_calls();
        mock_clear_system_states();
    }
};

TEST_F(DispatcherTest, BoardIdAndVersion) {
    {
        StdoutCapture capture;
        microhil_cmd_t cmd = {CMD_TYPE_SYS_ID, {}};
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#mh:333:2023:0#end>\n");
    }
    {
        StdoutCapture capture;
        microhil_cmd_t cmd = {CMD_TYPE_SYS_VERSION, {}};
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#microHIL v1.0.0#end>\n");
    }
}

TEST_F(DispatcherTest, SystemReset) {
    StdoutCapture capture;
    microhil_cmd_t cmd = {CMD_TYPE_SYS_RESET, {}};
    
    EXPECT_THROW(microhil_dispatcher_execute(&cmd), std::runtime_error);
    
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#system resetting...#end>\n");
    
    EXPECT_TRUE(buzzer_beep_stop_called);
    EXPECT_TRUE(buzzer_close_called);
    EXPECT_TRUE(led_close_called);
    
    ASSERT_EQ(nuttx_relay_calls.size(), 1);
    EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::CLOSE);
}

TEST_F(DispatcherTest, ChannelControl) {
    {
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_ON;
        cmd.data.ch.ch_idx = 0;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channel 1 on#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::SET);
        EXPECT_EQ(nuttx_relay_calls[0].channel, 0);
        EXPECT_TRUE(nuttx_relay_calls[0].state);
    }
    {
        mock_clear_relay_calls();
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_OFF;
        cmd.data.ch.ch_idx = 7;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channel 8 off#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::SET);
        EXPECT_EQ(nuttx_relay_calls[0].channel, 7);
        EXPECT_FALSE(nuttx_relay_calls[0].state);
    }
}

TEST_F(DispatcherTest, AllChannelsControl) {
    {
        StdoutCapture capture;
        microhil_cmd_t cmd = {CMD_TYPE_ALL_ON, {}};
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#all channels on#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::SET_ALL);
        EXPECT_TRUE(nuttx_relay_calls[0].state);
        EXPECT_EQ(mock_led_r, 255);
        EXPECT_EQ(mock_led_g, 255);
        EXPECT_EQ(mock_led_b, 255);
    }
    {
        mock_clear_relay_calls();
        StdoutCapture capture;
        microhil_cmd_t cmd = {CMD_TYPE_ALL_OFF, {}};
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#all channels off#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::SET_ALL);
        EXPECT_FALSE(nuttx_relay_calls[0].state);
        EXPECT_EQ(mock_led_r, 0);
        EXPECT_EQ(mock_led_g, 0);
        EXPECT_EQ(mock_led_b, 0);
    }
}

TEST_F(DispatcherTest, TimerPulseBlink) {
    {
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_TMR;
        cmd.data.ch.ch_idx = 2;
        cmd.data.ch.args.timer_sec = 15;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channel 3 timer started: 15 seconds#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::TIMER);
        EXPECT_EQ(nuttx_relay_calls[0].channel, 2);
        EXPECT_EQ(nuttx_relay_calls[0].timer_seconds, 15);
    }
    {
        mock_clear_relay_calls();
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_PULSE;
        cmd.data.ch.ch_idx = 4;
        cmd.data.ch.args.pulse_ms = 250;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channel 5 pulse started: 250 ms#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::PULSE);
        EXPECT_EQ(nuttx_relay_calls[0].channel, 4);
        EXPECT_EQ(nuttx_relay_calls[0].duration_ms, 250);
    }
    {
        mock_clear_relay_calls();
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_BLINK;
        cmd.data.ch.ch_idx = 1;
        cmd.data.ch.args.blink.on_ms = 100;
        cmd.data.ch.args.blink.off_ms = 200;
        cmd.data.ch.args.blink.count = 5;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channel 2 blink started: on=100 ms, off=200 ms, count=5#end>\n");
        ASSERT_EQ(nuttx_relay_calls.size(), 1);
        EXPECT_EQ(nuttx_relay_calls[0].type, NuttXRelayMockCall::BLINK);
        EXPECT_EQ(nuttx_relay_calls[0].channel, 1);
        EXPECT_EQ(nuttx_relay_calls[0].blink_on_ms, 100);
        EXPECT_EQ(nuttx_relay_calls[0].blink_off_ms, 200);
        EXPECT_EQ(nuttx_relay_calls[0].blink_count, 5);
    }
}

TEST_F(DispatcherTest, MaskCommand) {
    StdoutCapture capture;
    microhil_cmd_t cmd;
    cmd.type = CMD_TYPE_ALL_MASK;
    strcpy(cmd.data.mask, "10101010");
    microhil_dispatcher_execute(&cmd);
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channels mask applied: 10101010#end>\n");
    ASSERT_EQ(nuttx_relay_calls.size(), 8);
    for (uint32_t i = 0; i < 8; i++) {
        EXPECT_EQ(nuttx_relay_calls[i].type, NuttXRelayMockCall::SET);
        EXPECT_EQ(nuttx_relay_calls[i].channel, i);
        EXPECT_EQ(nuttx_relay_calls[i].state, (i % 2 == 0));
    }
}

TEST_F(DispatcherTest, StatusCommands) {
    {
        mock_set_channel_status(3, "relay 4 status description");
        StdoutCapture capture;
        microhil_cmd_t cmd;
        cmd.type = CMD_TYPE_CH_STAT;
        cmd.data.ch.ch_idx = 3;
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#relay 4 status description#end>\n");
    }
    {
        StdoutCapture capture;
        microhil_cmd_t cmd = {CMD_TYPE_ALL_STAT, {}};
        microhil_dispatcher_execute(&cmd);
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#channels: 1:OFF 2:OFF 3:OFF 4:OFF 5:OFF 6:OFF 7:OFF 8:OFF #end>\n");
    }
}
