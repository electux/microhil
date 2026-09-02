#pragma once

#include <queue>
#include <vector>
#include <string>
#include <stdint.h>
#include <stdbool.h>
#include "config/nvm_config.h"
#include "hardware/flash.h"

// Flash storage mock
extern uint8_t mock_flash_storage[PICO_FLASH_SIZE_BYTES];
void mock_clear_flash();

// Wi-Fi transport mock queues
extern std::queue<uint8_t> mock_wifi_rx_queue;
extern std::vector<uint8_t> mock_wifi_tx_buffer;
extern bool mock_wifi_connected;

void mock_push_wifi_rx(const std::string& str);
void mock_clear_wifi();

// USB-Serial mock queue
extern std::queue<char> mock_usb_rx_queue;
void mock_push_usb_rx(const std::string& str);
void mock_clear_usb();

// Wi-Fi manager mock
void mock_set_wifi_ip(const std::string& ip);
void mock_set_active_config(const nvm_wifi_config_t& cfg);

// Mock call registry for relay
struct RelayMockCall {
    enum CallType {
        SET, SET_ALL, TIMER, PULSE, BLINK
    } type;
    uint32_t channel;
    bool state;
    uint32_t timer_seconds;
    uint32_t duration_ms;
    uint32_t blink_on_ms;
    uint32_t blink_off_ms;
    uint32_t blink_count;
};

extern std::vector<RelayMockCall> relay_calls;
void mock_clear_relay_calls();
void mock_set_channel_status(uint32_t channel, const std::string& status);
void mock_trigger_relay_callback(uint32_t channel, bool state);
bool mock_has_relay_callback();

// Mock states for buzzer, status_led, watchdog
extern bool buzzer_beep_stop_called;
extern uint8_t mock_led_r;
extern uint8_t mock_led_g;
extern uint8_t mock_led_b;
extern bool watchdog_reboot_called;

void mock_clear_system_states();
