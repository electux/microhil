#pragma once

#include <queue>
#include <vector>
#include <string>
#include <stdint.h>
#include <stdbool.h>

// Mock queue for BLE incoming data
extern std::queue<uint8_t> mock_ble_rx_queue;
extern std::vector<uint8_t> mock_ble_tx_buffer;
extern bool mock_ble_connected;

void mock_push_ble_rx(const std::string& str);
void mock_clear_ble();

// Mock queue for USB serial incoming data
extern std::queue<uint8_t> mock_usb_rx_queue;
void mock_push_usb_rx(const std::string& str);
void mock_clear_usb();

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

// Mock states for buzzer, status_led, watchdog, flash
extern bool buzzer_beep_stop_called;
extern uint8_t mock_led_r;
extern uint8_t mock_led_g;
extern uint8_t mock_led_b;
extern bool watchdog_reboot_called;

void mock_clear_system_states();
void mock_flash_reset(bool fill_with_ff = true);
