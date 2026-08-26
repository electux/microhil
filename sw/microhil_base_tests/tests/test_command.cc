#include "gtest/gtest.h"
#include "mocks/mocks.h"
#include "command/dispatcher.h"
#include <unistd.h>
#include <fcntl.h>
#include <string>

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

class CommandTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_relay_calls();
        mock_clear_system_states();
    }
};

TEST_F(CommandTest, BoardIdAndVersion) {
    {
        StdoutCapture capture;
        command_dispatch("mh#sys#id#end");
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#mh:333:2023:0#end>");
    }
    {
        StdoutCapture capture;
        command_dispatch("mh#sys#version#end");
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#microHIL v1.0.0#end>");
    }
}

TEST_F(CommandTest, ChannelControl) {
    StdoutCapture capture;
    command_dispatch("mh#ch#1#on#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channel 1 on#end>");
    ASSERT_EQ(relay_calls.size(), 1);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET);
    EXPECT_EQ(relay_calls[0].channel, 0);
    EXPECT_TRUE(relay_calls[0].state);

    mock_clear_relay_calls();
    {
        StdoutCapture capture2;
        command_dispatch("mh#ch#8#off#end");
        std::string output2 = capture2.GetCapture();
        EXPECT_EQ(output2, "<mh#sys#channel 8 off#end>");
    }
    ASSERT_EQ(relay_calls.size(), 1);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET);
    EXPECT_EQ(relay_calls[0].channel, 7);
    EXPECT_FALSE(relay_calls[0].state);
}

TEST_F(CommandTest, AllChannelsControl) {
    {
        StdoutCapture capture;
        command_dispatch("mh#all#on#end");
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#all channels on#end>");
        ASSERT_EQ(relay_calls.size(), 1);
        EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET_ALL);
        EXPECT_TRUE(relay_calls[0].state);
        EXPECT_EQ(mock_led_r, 255);
        EXPECT_EQ(mock_led_g, 255);
        EXPECT_EQ(mock_led_b, 255);
    }
    {
        mock_clear_relay_calls();
        StdoutCapture capture;
        command_dispatch("mh#all#off#end");
        std::string output = capture.GetCapture();
        EXPECT_EQ(output, "<mh#sys#all channels off#end>");
        ASSERT_EQ(relay_calls.size(), 1);
        EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET_ALL);
        EXPECT_FALSE(relay_calls[0].state);
        EXPECT_EQ(mock_led_r, 0);
        EXPECT_EQ(mock_led_g, 0);
        EXPECT_EQ(mock_led_b, 0);
    }
}

TEST_F(CommandTest, TimerCommand) {
    StdoutCapture capture;
    command_dispatch("mh#ch#3#tmr#15#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channel 3 timer started: 15 seconds#end>");
    ASSERT_EQ(relay_calls.size(), 1);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::TIMER);
    EXPECT_EQ(relay_calls[0].channel, 2);
    EXPECT_EQ(relay_calls[0].timer_seconds, 15);
}

TEST_F(CommandTest, PulseCommand) {
    StdoutCapture capture;
    command_dispatch("mh#ch#5#pulse#250#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channel 5 pulse started: 250 ms#end>");
    ASSERT_EQ(relay_calls.size(), 1);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::PULSE);
    EXPECT_EQ(relay_calls[0].channel, 4);
    EXPECT_EQ(relay_calls[0].duration_ms, 250);
}

TEST_F(CommandTest, BlinkCommand) {
    StdoutCapture capture;
    command_dispatch("mh#ch#2#blink#100#200#5#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channel 2 blink started: on=100 ms, off=200 ms, count=5#end>");
    ASSERT_EQ(relay_calls.size(), 1);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::BLINK);
    EXPECT_EQ(relay_calls[0].channel, 1);
    EXPECT_EQ(relay_calls[0].blink_on_ms, 100);
    EXPECT_EQ(relay_calls[0].blink_off_ms, 200);
    EXPECT_EQ(relay_calls[0].blink_count, 5);
}

TEST_F(CommandTest, MaskCommand) {
    StdoutCapture capture;
    command_dispatch("mh#all#mask#10101010#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channels mask applied: 10101010#end>");
    ASSERT_EQ(relay_calls.size(), 8);
    for (uint32_t i = 0; i < 8; i++) {
        EXPECT_EQ(relay_calls[i].type, RelayMockCall::SET);
        EXPECT_EQ(relay_calls[i].channel, i);
        EXPECT_EQ(relay_calls[i].state, (i % 2 == 0));
    }
}

TEST_F(CommandTest, ChannelStatus) {
    mock_set_channel_status(3, "channel 4: ON (timer)");
    StdoutCapture capture;
    command_dispatch("mh#ch#4#stat#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channel 4: ON (timer)#end>");
}

TEST_F(CommandTest, AllStatus) {
    StdoutCapture capture;
    command_dispatch("mh#all#stat#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#channels: 1:OFF 2:OFF 3:OFF 4:OFF 5:OFF 6:OFF 7:OFF 8:OFF #end>");
}

TEST_F(CommandTest, SystemReset) {
    StdoutCapture capture;
    command_dispatch("mh#sys#reset#end");
    std::string output = capture.GetCapture();
    EXPECT_EQ(output, "<mh#sys#system resetting...#end>");
    EXPECT_TRUE(buzzer_beep_stop_called);
    EXPECT_TRUE(watchdog_reboot_called);
}
