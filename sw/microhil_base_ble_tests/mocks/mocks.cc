#include "mocks.h"
#include "device/buzzer.h"
#include "device/relay.h"
#include "device/status_led.h"
#include "ble/ble_transport.h"
#include "hardware/watchdog.h"
#include "hardware/flash.h"
#include <cstring>
#include <map>

std::queue<uint8_t> mock_ble_rx_queue;
std::vector<uint8_t> mock_ble_tx_buffer;
bool mock_ble_connected = true;

std::queue<uint8_t> mock_usb_rx_queue;
uint8_t mock_flash_storage[PICO_FLASH_SIZE_BYTES];

std::vector<RelayMockCall> relay_calls;
static std::map<uint32_t, std::string> mock_channel_statuses;
static relay_state_cb_t registered_relay_callback = nullptr;

bool buzzer_beep_stop_called = false;
uint8_t mock_led_r = 0;
uint8_t mock_led_g = 0;
uint8_t mock_led_b = 0;
bool watchdog_reboot_called = false;

void mock_push_ble_rx(const std::string& str) {
    for (char c : str) {
        mock_ble_rx_queue.push(static_cast<uint8_t>(c));
    }
}

void mock_clear_ble() {
    while (!mock_ble_rx_queue.empty()) {
        mock_ble_rx_queue.pop();
    }
    mock_ble_tx_buffer.clear();
    mock_ble_connected = true;
}

void mock_push_usb_rx(const std::string& str) {
    for (char c : str) {
        mock_usb_rx_queue.push(static_cast<uint8_t>(c));
    }
}

void mock_clear_usb() {
    while (!mock_usb_rx_queue.empty()) {
        mock_usb_rx_queue.pop();
    }
}

void mock_clear_relay_calls() {
    relay_calls.clear();
    mock_channel_statuses.clear();
}

void mock_set_channel_status(uint32_t channel, const std::string& status) {
    mock_channel_statuses[channel] = status;
}

void mock_trigger_relay_callback(uint32_t channel, bool state) {
    if (registered_relay_callback != nullptr) {
        registered_relay_callback(channel, state);
    }
}

bool mock_has_relay_callback() {
    return registered_relay_callback != nullptr;
}

void mock_clear_system_states() {
    buzzer_beep_stop_called = false;
    mock_led_r = 0;
    mock_led_g = 0;
    mock_led_b = 0;
    watchdog_reboot_called = false;
}

void mock_flash_reset(bool fill_with_ff) {
    memset(mock_flash_storage, fill_with_ff ? 0xFF : 0x00, sizeof(mock_flash_storage));
}

extern "C" {

uint32_t save_and_disable_interrupts(void) {
    return 0;
}

void restore_interrupts(uint32_t status) {
    (void)status;
}

void flash_range_erase(uint32_t offset, size_t count) {
    if (offset + count <= sizeof(mock_flash_storage)) {
        memset(&mock_flash_storage[offset], 0xFF, count);
    }
}

void flash_range_program(uint32_t offset, const uint8_t *data, size_t count) {
    if (offset + count <= sizeof(mock_flash_storage)) {
        memcpy(&mock_flash_storage[offset], data, count);
    }
}

bool ble_transport_read_byte(uint8_t *byte) {
    if (mock_ble_rx_queue.empty()) {
        return false;
    }
    *byte = mock_ble_rx_queue.front();
    mock_ble_rx_queue.pop();
    return true;
}

bool ble_transport_send(const uint8_t *data, uint16_t length) {
    if (!mock_ble_connected) {
        return false;
    }
    mock_ble_tx_buffer.insert(mock_ble_tx_buffer.end(), data, data + length);
    return true;
}

bool ble_transport_is_connected(void) {
    return mock_ble_connected;
}

const nvm_ble_config_t *ble_transport_get_config(void) {
    return nvm_config_get();
}

bool relay_init(void) {
    return true;
}

void relay_set(uint32_t channel, bool state) {
    RelayMockCall call;
    call.type = RelayMockCall::SET;
    call.channel = channel;
    call.state = state;
    relay_calls.push_back(call);
}

void relay_set_all(bool state) {
    RelayMockCall call;
    call.type = RelayMockCall::SET_ALL;
    call.state = state;
    relay_calls.push_back(call);
}

void relay_start_timer(uint32_t channel, uint32_t seconds) {
    RelayMockCall call;
    call.type = RelayMockCall::TIMER;
    call.channel = channel;
    call.timer_seconds = seconds;
    relay_calls.push_back(call);
}

void relay_start_pulse(uint32_t channel, uint32_t duration_ms) {
    RelayMockCall call;
    call.type = RelayMockCall::PULSE;
    call.channel = channel;
    call.duration_ms = duration_ms;
    relay_calls.push_back(call);
}

void relay_start_blink(uint32_t channel, uint32_t on_time_ms, uint32_t off_time_ms, uint32_t count) {
    RelayMockCall call;
    call.type = RelayMockCall::BLINK;
    call.channel = channel;
    call.blink_on_ms = on_time_ms;
    call.blink_off_ms = off_time_ms;
    call.blink_count = count;
    relay_calls.push_back(call);
}

void relay_get_status(uint32_t channel, char *buf, uint32_t max_len) {
    if (mock_channel_statuses.find(channel) != mock_channel_statuses.end()) {
        strncpy(buf, mock_channel_statuses[channel].c_str(), max_len - 1);
        buf[max_len - 1] = '\0';
    } else {
        snprintf(buf, max_len, "channel %u: OFF", channel + 1);
    }
}

void relay_set_state_callback(relay_state_cb_t cb) {
    registered_relay_callback = cb;
}

void relay_tick(void) {}

bool buzzer_init(void) {
    return true;
}

void buzzer_write(uint16_t value) {
    (void)value;
}

void buzzer_beep_start(void) {}

void buzzer_beep_changed(void) {}

void buzzer_beep_stop(void) {
    buzzer_beep_stop_called = true;
}

void buzzer_tick(void) {}

bool status_led_init(void) {
    return true;
}

void status_led_write(uint8_t red, uint8_t green, uint8_t blue) {
    mock_led_r = red;
    mock_led_g = green;
    mock_led_b = blue;
}

void watchdog_reboot(uint32_t pc, uint32_t sp, uint32_t delay_ms) {
    (void)pc;
    (void)sp;
    (void)delay_ms;
    watchdog_reboot_called = true;
}

int getchar_timeout_us(uint32_t timeout_us) {
    (void)timeout_us;
    if (mock_usb_rx_queue.empty()) {
        return -1;
    }
    uint8_t c = mock_usb_rx_queue.front();
    mock_usb_rx_queue.pop();
    return c;
}

}
