#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <stdbool.h>

struct NuttXRelayMockCall {
    enum CallType {
        SET, SET_ALL, TIMER, PULSE, BLINK, CLOSE
    } type;
    uint32_t channel;
    bool state;
    uint32_t timer_seconds;
    uint32_t duration_ms;
    uint32_t blink_on_ms;
    uint32_t blink_off_ms;
    uint32_t blink_count;
};

extern std::vector<NuttXRelayMockCall> nuttx_relay_calls;
void mock_clear_relay_calls();
void mock_set_channel_status(uint32_t channel, const std::string& status);

extern bool buzzer_beep_stop_called;
extern bool buzzer_close_called;
extern bool led_close_called;
extern uint8_t mock_led_r;
extern uint8_t mock_led_g;
extern uint8_t mock_led_b;

void mock_clear_system_states();
