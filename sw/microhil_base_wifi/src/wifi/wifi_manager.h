/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * wifi_manager.h
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

#include "config/nvm_config.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes CYW43 Wi-Fi hardware and starts AP or STA mode
/// @param config [in] Pointer to active network configuration
/// @return True on success, false on initialization error
bool wifi_manager_init(const nvm_wifi_config_t *config);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if Wi-Fi link is up and connected
/// @return True if connected/active, false otherwise
bool wifi_manager_is_connected(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Returns the active IP address string
/// @return Null-terminated IP string (e.g. "192.168.4.1")
const char *wifi_manager_get_ip(void);

#ifdef __cplusplus
}
#endif
