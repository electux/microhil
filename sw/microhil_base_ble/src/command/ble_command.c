/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_command.c
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
#include "ble_command.h"
#include "ble/ble_transport.h"
#include "config/nvm_config.h"
#include "device/buzzer.h"
#include "hardware/watchdog.h"
#include "response.h"
#include <stdio.h>
#include <string.h>

void ble_command_handle_get(const char *cmd_str) {
  (void)cmd_str;
  const nvm_ble_config_t *cfg = ble_transport_get_config();
  response_send_formatted(
      "<mh#ble#cfg#%s#%u#%u#end>", cfg->device_name, cfg->adv_interval_ms,
      cfg->passkey
  );
}

void ble_command_handle_set(const char *cmd_str) {
  nvm_ble_config_t new_cfg;
  memset(&new_cfg, 0, sizeof(nvm_ble_config_t));

  char device_name[NVM_NAME_MAX_LEN] = {0};
  uint32_t adv_interval = 0;
  uint32_t passkey = 0;

  if (sscanf(
          cmd_str, "mh#ble#set#%31[^#]#%u#%u#end", device_name, &adv_interval,
          &passkey
      ) == 3) {
    strncpy(new_cfg.device_name, device_name, sizeof(new_cfg.device_name) - 1);
    new_cfg.adv_interval_ms = (uint16_t)adv_interval;
    new_cfg.passkey = passkey;

    if (nvm_config_save(&new_cfg)) {
      response_send("<mh#ble#ok#restarting#end>");
      buzzer_beep_stop();
      watchdog_reboot(0, 0, 100);
      return;
    }
  }

  response_send("<mh#ble#error#invalid_parameters#end>");
}

void ble_command_handle_reset(const char *cmd_str) {
  (void)cmd_str;
  if (nvm_config_reset_to_default()) {
    response_send("<mh#ble#ok#default_restored#end>");
    buzzer_beep_stop();
    watchdog_reboot(0, 0, 100);
  } else {
    response_send("<mh#ble#error#reset_failed#end>");
  }
}
