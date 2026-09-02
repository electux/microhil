#include <gtest/gtest.h>
#include "command/dispatcher.h"
#include "mocks/mocks.h"

class WifiCommandTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_flash();
        mock_clear_wifi();
        mock_clear_usb();
        mock_clear_relay_calls();
        mock_clear_system_states();

        nvm_wifi_config_t default_cfg;
        nvm_config_get_default(&default_cfg);
        nvm_config_save(&default_cfg);
        mock_set_active_config(default_cfg);
        mock_set_wifi_ip("192.168.4.1");

        command_init();
    }
};

TEST_F(WifiCommandTest, BoardIdAndVersion) {
    command_dispatch("mh#sys#id#end");
    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#mh:333:2023:0:wifi#end>"), std::string::npos);

    mock_clear_wifi();
    command_dispatch("mh#sys#version#end");
    resp.assign(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#microHIL-WIFI v1.0.0#end>"), std::string::npos);
}

TEST_F(WifiCommandTest, NetworkGetConfig) {
    command_dispatch("mh#net#get#end");
    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#net#cfg#AP#microhil-wifi#192.168.4.1#5000#end>"), std::string::npos);
}

TEST_F(WifiCommandTest, NetworkSetApConfig) {
    command_dispatch("mh#net#set#ap#my-ap#secret999#192.168.5.1#6000#end");
    EXPECT_TRUE(watchdog_reboot_called);

    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#net#ok#restarting#end>"), std::string::npos);

    nvm_wifi_config_t reloaded;
    nvm_config_init(&reloaded);
    EXPECT_EQ(reloaded.mode, (uint8_t)WIFI_MODE_AP);
    EXPECT_STREQ(reloaded.ssid, "my-ap");
    EXPECT_STREQ(reloaded.password, "secret999");
    EXPECT_STREQ(reloaded.ip, "192.168.5.1");
    EXPECT_EQ(reloaded.port, 6000);
}

TEST_F(WifiCommandTest, NetworkSetStaConfig) {
    command_dispatch("mh#net#set#sta#OfficeNet#Passw0rd#5000#end");
    EXPECT_TRUE(watchdog_reboot_called);

    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#net#ok#restarting#end>"), std::string::npos);

    nvm_wifi_config_t reloaded;
    nvm_config_init(&reloaded);
    EXPECT_EQ(reloaded.mode, (uint8_t)WIFI_MODE_STA);
    EXPECT_STREQ(reloaded.ssid, "OfficeNet");
    EXPECT_STREQ(reloaded.password, "Passw0rd");
    EXPECT_EQ(reloaded.port, 5000);
}

TEST_F(WifiCommandTest, NetworkResetConfig) {
    // Write non-default config first
    nvm_wifi_config_t temp;
    memset(&temp, 0, sizeof(temp));
    temp.mode = (uint8_t)WIFI_MODE_STA;
    strncpy(temp.ssid, "temp", sizeof(temp.ssid) - 1);
    nvm_config_save(&temp);

    command_dispatch("mh#net#reset#end");
    EXPECT_TRUE(watchdog_reboot_called);

    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#net#ok#default_restored#end>"), std::string::npos);

    nvm_wifi_config_t reloaded;
    nvm_config_init(&reloaded);
    EXPECT_EQ(reloaded.mode, (uint8_t)WIFI_MODE_AP);
    EXPECT_STREQ(reloaded.ssid, "microhil-wifi");
}

TEST_F(WifiCommandTest, ChannelControl) {
    command_dispatch("mh#ch#1#on#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET);
    EXPECT_EQ(relay_calls[0].channel, 0u);
    EXPECT_TRUE(relay_calls[0].state);

    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#channel 1 on#end>"), std::string::npos);
}

TEST_F(WifiCommandTest, AllChannelsControl) {
    command_dispatch("mh#all#on#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET_ALL);
    EXPECT_TRUE(relay_calls[0].state);
    EXPECT_EQ(mock_led_r, 255);
    EXPECT_EQ(mock_led_g, 255);
    EXPECT_EQ(mock_led_b, 255);

    mock_clear_relay_calls();
    command_dispatch("mh#all#off#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET_ALL);
    EXPECT_FALSE(relay_calls[0].state);
    EXPECT_EQ(mock_led_r, 0);
    EXPECT_EQ(mock_led_g, 0);
    EXPECT_EQ(mock_led_b, 0);
}

TEST_F(WifiCommandTest, TimerPulseBlinkMask) {
    command_dispatch("mh#ch#2#tmr#15#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::TIMER);
    EXPECT_EQ(relay_calls[0].channel, 1u);
    EXPECT_EQ(relay_calls[0].timer_seconds, 15u);

    mock_clear_relay_calls();
    command_dispatch("mh#ch#5#pulse#300#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::PULSE);
    EXPECT_EQ(relay_calls[0].channel, 4u);
    EXPECT_EQ(relay_calls[0].duration_ms, 300u);

    mock_clear_relay_calls();
    command_dispatch("mh#ch#6#blink#200#300#3#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::BLINK);
    EXPECT_EQ(relay_calls[0].channel, 5u);
    EXPECT_EQ(relay_calls[0].blink_on_ms, 200u);
    EXPECT_EQ(relay_calls[0].blink_off_ms, 300u);
    EXPECT_EQ(relay_calls[0].blink_count, 3u);

    mock_clear_relay_calls();
    command_dispatch("mh#all#mask#01010101#end");
    ASSERT_EQ(relay_calls.size(), 8u);
    EXPECT_FALSE(relay_calls[0].state);
    EXPECT_TRUE(relay_calls[1].state);
}

TEST_F(WifiCommandTest, SystemReset) {
    command_dispatch("mh#sys#reset#end");
    EXPECT_TRUE(buzzer_beep_stop_called);
    EXPECT_TRUE(watchdog_reboot_called);
}

TEST_F(WifiCommandTest, AsyncRelayOffNotification) {
    EXPECT_TRUE(mock_has_relay_callback());
    mock_trigger_relay_callback(4, false);

    std::string resp(mock_wifi_tx_buffer.begin(), mock_wifi_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#channel 5 off#end>"), std::string::npos);
}
