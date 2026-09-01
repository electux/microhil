/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * relay.c
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-ble is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-ble is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "relay.h"
#include "buzzer.h"
#include "io/io_gpio.h"
#include "pico/stdlib.h"
#include <stddef.h>
#include <stdio.h>

static const uint32_t relay_pins[RELAY_NUM_CHANNELS] = {
    21, 20, 19, 18, 17, 16, 15, 14,
};

static const uint64_t US_TO_MS = 1000;
static const uint64_t MS_TO_SEC = 1000;

typedef struct {
  relay_mode_t mode;
  bool active;
  uint64_t start_time;
  uint64_t duration_ms;
  uint32_t blink_on_ms;
  uint32_t blink_off_ms;
  uint32_t blink_count;
  bool blink_phase;
} relay_state_internal_t;

static relay_state_internal_t relay_states[RELAY_NUM_CHANNELS];
static bool current_phys_state[RELAY_NUM_CHANNELS] = {false};
static relay_state_cb_t s_state_callback = NULL;

bool relay_init(void) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    io_gpio_init(relay_pins[i], true);
    io_gpio_write(relay_pins[i], true);
    current_phys_state[i] = false;
    
    relay_states[i].mode = RELAY_MODE_TOGGLE;
    relay_states[i].active = false;
    relay_states[i].start_time = 0;
    relay_states[i].duration_ms = 0;
    relay_states[i].blink_on_ms = 0;
    relay_states[i].blink_off_ms = 0;
    relay_states[i].blink_count = 0;
    relay_states[i].blink_phase = false;
  }
  return true;
}

void relay_set_state_callback(relay_state_cb_t callback) {
  s_state_callback = callback;
}

static void relay_set_phys(uint32_t channel, bool state) {
  if (channel < RELAY_NUM_CHANNELS) {
    if (current_phys_state[channel] != state) {
      current_phys_state[channel] = state;
      io_gpio_write(relay_pins[channel], !state);
      buzzer_beep_changed();
    }
  }
}

void relay_set(uint32_t channel, bool state) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].active = false;
    relay_states[channel].mode = RELAY_MODE_TOGGLE;
    relay_set_phys(channel, state);
  }
}

void relay_set_all(bool state) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    relay_set(i, state);
  }
}

void relay_start_timer(uint32_t channel, uint32_t seconds) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].mode = RELAY_MODE_TIMER;
    relay_states[channel].active = true;
    relay_states[channel].start_time = time_us_64() / US_TO_MS;
    relay_states[channel].duration_ms = (uint64_t)seconds * MS_TO_SEC;
    relay_set_phys(channel, true);
  }
}

void relay_start_pulse(uint32_t channel, uint32_t duration_ms) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].mode = RELAY_MODE_PULSE;
    relay_states[channel].active = true;
    relay_states[channel].start_time = time_us_64() / US_TO_MS;
    relay_states[channel].duration_ms = duration_ms;
    relay_set_phys(channel, true);
  }
}

void relay_start_blink(uint32_t channel, uint32_t on_ms, uint32_t off_ms, uint32_t count) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].mode = RELAY_MODE_BLINK;
    relay_states[channel].active = true;
    relay_states[channel].blink_on_ms = on_ms;
    relay_states[channel].blink_off_ms = off_ms;
    relay_states[channel].blink_count = count;
    relay_states[channel].blink_phase = true;
    relay_states[channel].start_time = time_us_64() / US_TO_MS;
    relay_set_phys(channel, true);
  }
}

void relay_tick(void) {
  uint64_t now_ms = time_us_64() / US_TO_MS;
  for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
    if (!relay_states[i].active) {
      continue;
    }

    if (relay_states[i].mode == RELAY_MODE_TIMER || relay_states[i].mode == RELAY_MODE_PULSE) {
      if (now_ms - relay_states[i].start_time >= relay_states[i].duration_ms) {
        relay_set_phys(i, false);
        relay_states[i].active = false;
        relay_states[i].mode = RELAY_MODE_TOGGLE;
        if (s_state_callback != NULL) {
          s_state_callback(i, false);
        }
      }
    } else if (relay_states[i].mode == RELAY_MODE_BLINK) {
      if (relay_states[i].blink_phase) {
        if (now_ms - relay_states[i].start_time >= relay_states[i].blink_on_ms) {
          relay_set_phys(i, false);
          relay_states[i].blink_phase = false;
          relay_states[i].start_time = now_ms;
        }
      } else {
        if (now_ms - relay_states[i].start_time >= relay_states[i].blink_off_ms) {
          if (relay_states[i].blink_count > 0) {
            relay_states[i].blink_count--;
            if (relay_states[i].blink_count == 0) {
              relay_states[i].active = false;
              relay_states[i].mode = RELAY_MODE_TOGGLE;
              if (s_state_callback != NULL) {
                s_state_callback(i, false);
              }
              continue;
            }
          }
          relay_set_phys(i, true);
          relay_states[i].blink_phase = true;
          relay_states[i].start_time = now_ms;
        }
      }
    }
  }
}

void relay_get_status(uint32_t channel, char *buf, uint32_t max_len) {
  if (channel >= RELAY_NUM_CHANNELS) {
    snprintf(buf, max_len, "invalid channel");
    return;
  }

  const char *phys_state = current_phys_state[channel] ? "ON" : "OFF";
  if (!relay_states[channel].active) {
    snprintf(buf, max_len, "Channel %u: %s (Toggle)", channel + 1, phys_state);
  } else {
    switch (relay_states[channel].mode) {
      case RELAY_MODE_TIMER: {
        uint64_t elapsed = time_us_64() / US_TO_MS - relay_states[channel].start_time;
        uint64_t remaining = (relay_states[channel].duration_ms > elapsed) ? 
                             (relay_states[channel].duration_ms - elapsed) : 0;
        snprintf(buf, max_len, "Channel %u: %s (Timer, rem: %llus)",
                 channel + 1, phys_state, remaining / MS_TO_SEC);
        break;
      }
      case RELAY_MODE_PULSE: {
        uint64_t elapsed = time_us_64() / US_TO_MS - relay_states[channel].start_time;
        uint64_t remaining = (relay_states[channel].duration_ms > elapsed) ? 
                             (relay_states[channel].duration_ms - elapsed) : 0;
        snprintf(buf, max_len, "Channel %u: %s (Pulse, rem: %llums)",
                 channel + 1, phys_state, remaining);
        break;
      }
      case RELAY_MODE_BLINK:
        snprintf(buf, max_len, "Channel %u: %s (Blink, count: %u, phase: %s)",
                 channel + 1, phys_state, relay_states[channel].blink_count,
                 relay_states[channel].blink_phase ? "ON" : "OFF");
        break;
      default:
        snprintf(buf, max_len, "Channel %u: %s", channel + 1, phys_state);
        break;
    }
  }
}
