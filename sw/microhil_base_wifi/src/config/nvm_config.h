/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * nvm_config.h
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-wifi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-wifi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "wifi_default_config.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NVM_SSID_MAX_LEN 32
#define NVM_PASS_MAX_LEN 64
#define NVM_IP_MAX_LEN 16

////////////////////////////////////////////////////////////////////////////
/// @brief Wi-Fi operation modes
typedef enum {
  WIFI_MODE_AP = DEFAULT_WIFI_MODE_AP,
  WIFI_MODE_STA = DEFAULT_WIFI_MODE_STA
} wifi_op_mode_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Persistent Wi-Fi configuration record stored in RP2040 Flash memory
typedef struct {
  uint32_t magic;                  ///< Magic header validator (0x4D48494C 'MHIL')
  uint32_t version;                ///< Structure layout version
  uint8_t mode;                    ///< Active mode: 0 (AP) or 1 (STA)
  char ssid[NVM_SSID_MAX_LEN];     ///< SSID string
  char password[NVM_PASS_MAX_LEN]; ///< WPA2-PSK password
  char ip[NVM_IP_MAX_LEN];         ///< Static IP string for AP mode
  uint16_t port;                   ///< TCP server port (e.g. 5000)
  uint32_t checksum;               ///< Data integrity checksum
} nvm_wifi_config_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes NVM subsystem and loads active config from Flash or default
/// @param config [out] Destination structure to populate
void nvm_config_init(nvm_wifi_config_t *config);

////////////////////////////////////////////////////////////////////////////
/// @brief Erases flash sector and writes new configuration to RP2040 Flash memory
/// @param config [in] Configuration structure to persist
/// @return True on successful write and verification, false otherwise
bool nvm_config_save(const nvm_wifi_config_t *config);

////////////////////////////////////////////////////////////////////////////
/// @brief Restores factory default network settings in Flash memory
/// @return True on success, false otherwise
bool nvm_config_reset_to_default(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Populates configuration structure with factory default parameters
/// @param config [out] Destination structure to populate
void nvm_config_get_default(nvm_wifi_config_t *config);

#ifdef __cplusplus
}
#endif
