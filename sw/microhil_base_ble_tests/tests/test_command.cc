#include <gtest/gtest.h>
#include "command/dispatcher.h"
#include "config/nvm_config.h"
#include "config/ble_default_config.h"
#include "mocks/mocks.h"
#include "mocks/hardware/flash.h"

class BleCommandTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_flash_reset(true);
        nvm_config_init();
        mock_clear_ble();
        mock_clear_relay_calls();
        mock_clear_system_states();
        command_init();
    }
};

TEST_F(BleCommandTest, BoardIdAndVersion) {
    command_dispatch("mh#sys#id#end");
    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#mh:333:2023:0:ble#end>"), std::string::npos);

    mock_clear_ble();
    command_dispatch("mh#sys#version#end");
    resp.assign(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#microHIL-BLE v1.0.0#end>"), std::string::npos);
}

TEST_F(BleCommandTest, BleGetConfig) {
    command_dispatch("mh#ble#get#end");
    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#ble#cfg#microhil-ble#50#0#end>"), std::string::npos);
}

TEST_F(BleCommandTest, BleSetConfig) {
    command_dispatch("mh#ble#set#microhil-custom#80#123456#end");
    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#ble#ok#restarting#end>"), std::string::npos);
    EXPECT_TRUE(watchdog_reboot_called);

    const nvm_ble_config_t *saved = nvm_config_get();
    EXPECT_STREQ(saved->device_name, "microhil-custom");
    EXPECT_EQ(saved->adv_interval_ms, 80);
    EXPECT_EQ(saved->passkey, 123456u);
}

TEST_F(BleCommandTest, BleResetConfig) {
    nvm_ble_config_t custom_cfg;
    memset(&custom_cfg, 0, sizeof(custom_cfg));
    strncpy(custom_cfg.device_name, "custom-node", sizeof(custom_cfg.device_name) - 1);
    nvm_config_save(&custom_cfg);

    command_dispatch("mh#ble#reset#end");
    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#ble#ok#default_restored#end>"), std::string::npos);
    EXPECT_TRUE(watchdog_reboot_called);

    const nvm_ble_config_t *def = nvm_config_get();
    EXPECT_STREQ(def->device_name, DEFAULT_BLE_DEVICE_NAME);
}

TEST_F(BleCommandTest, ChannelControl) {
    command_dispatch("mh#ch#1#on#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET);
    EXPECT_EQ(relay_calls[0].channel, 0u);
    EXPECT_TRUE(relay_calls[0].state);

    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#channel 1 on#end>"), std::string::npos);

    mock_clear_ble();
    mock_clear_relay_calls();

    command_dispatch("mh#ch#8#off#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::SET);
    EXPECT_EQ(relay_calls[0].channel, 7u);
    EXPECT_FALSE(relay_calls[0].state);

    resp.assign(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#channel 8 off#end>"), std::string::npos);
}

TEST_F(BleCommandTest, AllChannelsControl) {
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

TEST_F(BleCommandTest, TimerPulseBlinkMask) {
    // Timer
    command_dispatch("mh#ch#2#tmr#10#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::TIMER);
    EXPECT_EQ(relay_calls[0].channel, 1u);
    EXPECT_EQ(relay_calls[0].timer_seconds, 10u);

    // Pulse
    mock_clear_relay_calls();
    command_dispatch("mh#ch#3#pulse#500#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::PULSE);
    EXPECT_EQ(relay_calls[0].channel, 2u);
    EXPECT_EQ(relay_calls[0].duration_ms, 500u);

    // Blink
    mock_clear_relay_calls();
    command_dispatch("mh#ch#4#blink#100#200#5#end");
    ASSERT_EQ(relay_calls.size(), 1u);
    EXPECT_EQ(relay_calls[0].type, RelayMockCall::BLINK);
    EXPECT_EQ(relay_calls[0].channel, 3u);
    EXPECT_EQ(relay_calls[0].blink_on_ms, 100u);
    EXPECT_EQ(relay_calls[0].blink_off_ms, 200u);
    EXPECT_EQ(relay_calls[0].blink_count, 5u);

    // Mask
    mock_clear_relay_calls();
    command_dispatch("mh#all#mask#10101010#end");
    ASSERT_EQ(relay_calls.size(), 8u);
    EXPECT_TRUE(relay_calls[0].state);
    EXPECT_FALSE(relay_calls[1].state);
    EXPECT_TRUE(relay_calls[2].state);
    EXPECT_FALSE(relay_calls[3].state);
}

TEST_F(BleCommandTest, SystemReset) {
    command_dispatch("mh#sys#reset#end");
    EXPECT_TRUE(buzzer_beep_stop_called);
    EXPECT_TRUE(watchdog_reboot_called);

    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#system resetting...#end>"), std::string::npos);
}

TEST_F(BleCommandTest, AsyncRelayOffNotification) {
    EXPECT_TRUE(mock_has_relay_callback());
    mock_trigger_relay_callback(2, false);

    std::string resp(mock_ble_tx_buffer.begin(), mock_ble_tx_buffer.end());
    EXPECT_NE(resp.find("<mh#sys#channel 3 off#end>"), std::string::npos);
}
