/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * relay.h
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
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Total number of relay channels
enum { RELAY_NUM_CHANNELS = 8 };

////////////////////////////////////////////////////////////////////////////
/// @brief Relay modes
typedef enum {
  RELAY_MODE_TOGGLE,
  RELAY_MODE_TIMER,
  RELAY_MODE_PULSE,
  RELAY_MODE_BLINK
} relay_mode_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Relay state changed event callback function type
/// @param channel [in] Relay channel index (0 to RELAY_NUM_CHANNELS - 1)
/// @param state [in] True if ON, false if OFF
typedef void (*relay_state_cb_t)(uint32_t channel, bool state);

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes all relay GPIO channels
///
/// @return True if initialization succeeded, false otherwise
bool relay_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Sets the state of a specific relay channel
///
/// @param channel [in] Relay channel index (0 to RELAY_NUM_CHANNELS - 1)
/// @param state [in] True to turn ON, false to turn OFF
void relay_set(uint32_t channel, bool state);

////////////////////////////////////////////////////////////////////////////
/// @brief Sets the state of all relay channels simultaneously
///
/// @param state [in] True to turn all ON, false to turn all OFF
void relay_set_all(bool state);

////////////////////////////////////////////////////////////////////////////
/// @brief Starts a timer mode on a relay channel
void relay_start_timer(uint32_t channel, uint32_t seconds);

////////////////////////////////////////////////////////////////////////////
/// @brief Starts a pulse mode on a relay channel
void relay_start_pulse(uint32_t channel, uint32_t duration_ms);

////////////////////////////////////////////////////////////////////////////
/// @brief Starts a blink mode on a relay channel
void relay_start_blink(
    uint32_t channel, uint32_t on_ms, uint32_t off_ms, uint32_t count
);

////////////////////////////////////////////////////////////////////////////
/// @brief Non-blocking tick routine for relay timings
void relay_tick(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Returns a status string for the given relay channel
void relay_get_status(uint32_t channel, char *buf, uint32_t max_len);

////////////////////////////////////////////////////////////////////////////
/// @brief Registers an event callback for asynchronous relay state changes
/// @param callback [in] Callback function or NULL to unregister
void relay_set_state_callback(relay_state_cb_t callback);

#ifdef __cplusplus
}
#endif
