/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * nvm_config.h
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

#define NVM_BLE_MAGIC 0x4D48494C // 'MHIL'
#define NVM_BLE_CONFIG_VERSION 1
#define NVM_NAME_MAX_LEN 32

typedef struct {
  uint32_t magic;
  uint16_t version;
  char device_name[NVM_NAME_MAX_LEN];
  uint16_t adv_interval_ms;
  uint32_t passkey;
  uint16_t checksum;
} __attribute__((packed)) nvm_ble_config_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes NVM BLE configuration subsystem
/// @return true if valid configuration loaded, false if defaults restored
bool nvm_config_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Gets pointer to active in-memory BLE configuration
/// @return Read-only pointer to active nvm_ble_config_t
const nvm_ble_config_t *nvm_config_get(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Saves new BLE configuration to RP2040 Flash memory
/// @param new_cfg Pointer to configuration to be written
/// @return true if written and verified successfully, false otherwise
bool nvm_config_save(const nvm_ble_config_t *new_cfg);

////////////////////////////////////////////////////////////////////////////
/// @brief Resets configuration to factory defaults in Flash memory
/// @return true on success, false on failure
bool nvm_config_reset_to_default(void);

#ifdef __cplusplus
}
#endif
