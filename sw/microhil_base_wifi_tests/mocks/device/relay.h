#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum { RELAY_NUM_CHANNELS = 8 };

typedef enum {
  RELAY_MODE_TOGGLE,
  RELAY_MODE_TIMER,
  RELAY_MODE_PULSE,
  RELAY_MODE_BLINK
} relay_mode_t;

typedef void (*relay_state_cb_t)(uint32_t channel, bool state);

bool relay_init(void);
void relay_set(uint32_t channel, bool state);
void relay_set_all(bool state);
void relay_start_timer(uint32_t channel, uint32_t seconds);
void relay_start_pulse(uint32_t channel, uint32_t duration_ms);
void relay_start_blink(
    uint32_t channel, uint32_t on_ms, uint32_t off_ms, uint32_t count
);
void relay_tick(void);
void relay_get_status(uint32_t channel, char *buf, uint32_t max_len);
void relay_set_state_callback(relay_state_cb_t callback);

#ifdef __cplusplus
}
#endif
