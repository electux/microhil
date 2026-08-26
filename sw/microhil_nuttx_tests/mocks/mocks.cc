#include "mocks.h"
#include <nuttx/arch.h>
extern "C" {
#include "../microhil_nuttx/apps/microhil/controllers/microhil_relay.h"
#include "../microhil_nuttx/apps/microhil/controllers/microhil_led.h"
#include "../microhil_nuttx/apps/microhil/controllers/microhil_buzzer.h"
}
#include <stdexcept>
#include <cstdio>

std::vector<NuttXRelayMockCall> nuttx_relay_calls;
static std::string channel_statuses[RELAY_NUM_CHANNELS];

bool buzzer_beep_stop_called = false;
bool buzzer_close_called = false;
bool led_close_called = false;
uint8_t mock_led_r = 0;
uint8_t mock_led_g = 0;
uint8_t mock_led_b = 0;

void mock_clear_relay_calls() {
    nuttx_relay_calls.clear();
}

void mock_set_channel_status(uint32_t channel, const std::string& status) {
    if (channel < RELAY_NUM_CHANNELS) {
        channel_statuses[channel] = status;
    }
}

void mock_clear_system_states() {
    buzzer_beep_stop_called = false;
    buzzer_close_called = false;
    led_close_called = false;
    mock_led_r = 0;
    mock_led_g = 0;
    mock_led_b = 0;
    for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
        channel_statuses[i].clear();
    }
}

extern "C" {

void up_systemreset(void) {
    throw std::runtime_error("up_systemreset");
}

bool microhil_relay_init(void) {
    return true;
}

void microhil_relay_set(uint32_t channel, bool state) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::SET, channel, state, 0, 0, 0, 0, 0});
}

void microhil_relay_set_all(bool state) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::SET_ALL, 0, state, 0, 0, 0, 0, 0});
}

void microhil_relay_start_timer(uint32_t channel, uint32_t seconds) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::TIMER, channel, false, seconds, 0, 0, 0, 0});
}

void microhil_relay_start_pulse(uint32_t channel, uint32_t duration_ms) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::PULSE, channel, false, 0, duration_ms, 0, 0, 0});
}

void microhil_relay_start_blink(uint32_t channel, uint32_t on_ms, uint32_t off_ms, uint32_t count) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::BLINK, channel, false, 0, 0, on_ms, off_ms, count});
}

void microhil_relay_get_status(uint32_t channel, char *buf, size_t buf_len) {
    if (channel < RELAY_NUM_CHANNELS) {
        if (!channel_statuses[channel].empty()) {
            snprintf(buf, buf_len, "%s", channel_statuses[channel].c_str());
        } else {
            snprintf(buf, buf_len, "channel %u: OFF", channel + 1);
        }
    }
}

void microhil_relay_tick(void) {}

void microhil_relay_close(void) {
    nuttx_relay_calls.push_back({NuttXRelayMockCall::CLOSE, 0, false, 0, 0, 0, 0, 0});
}

bool microhil_led_init(void) {
    return true;
}

void microhil_led_write(uint8_t red, uint8_t green, uint8_t blue) {
    mock_led_r = red;
    mock_led_g = green;
    mock_led_b = blue;
}

void microhil_led_close(void) {
    led_close_called = true;
}

bool microhil_buzzer_init(void) {
    return true;
}

void microhil_buzzer_beep_start(void) {}
void microhil_buzzer_beep_changed(void) {}

void microhil_buzzer_beep_stop(void) {
    buzzer_beep_stop_called = true;
}

void microhil_buzzer_play_usb_fail(void) {}
void microhil_buzzer_play_usb_success(void) {}
void microhil_buzzer_tick(void) {}

void microhil_buzzer_close(void) {
    buzzer_close_called = true;
}

}
