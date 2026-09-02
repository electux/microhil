/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * net_command.c
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
#include "net_command.h"
#include "config/nvm_config.h"
#include "device/buzzer.h"
#include "hardware/watchdog.h"
#include "response.h"
#include "wifi/wifi_manager.h"
#include "wifi/wifi_transport.h"
#include <stdio.h>
#include <string.h>

void net_command_handle_get(const char *cmd_str) {
  (void)cmd_str;
  const nvm_wifi_config_t *cfg = wifi_transport_get_config();
  const char *mode_str = (cfg->mode == (uint8_t)WIFI_MODE_AP) ? "AP" : "STA";
  const char *ip_str = wifi_manager_get_ip();
  response_send_formatted(
      "<mh#net#cfg#%s#%s#%s#%u#end>", mode_str, cfg->ssid, ip_str, cfg->port
  );
}

void net_command_handle_set_ap(const char *cmd_str) {
  nvm_wifi_config_t new_cfg;
  memset(&new_cfg, 0, sizeof(nvm_wifi_config_t));
  new_cfg.mode = (uint8_t)WIFI_MODE_AP;

  char ssid[NVM_SSID_MAX_LEN] = {0};
  char pass[NVM_PASS_MAX_LEN] = {0};
  char ip[NVM_IP_MAX_LEN] = {0};
  uint32_t port = 0;

  if (sscanf(
          cmd_str, "mh#net#set#ap#%31[^#]#%63[^#]#%15[^#]#%u#end", ssid, pass,
          ip, &port
      ) == 4) {
    strncpy(new_cfg.ssid, ssid, sizeof(new_cfg.ssid) - 1);
    strncpy(new_cfg.password, pass, sizeof(new_cfg.password) - 1);
    strncpy(new_cfg.ip, ip, sizeof(new_cfg.ip) - 1);
    new_cfg.port = (uint16_t)port;

    if (nvm_config_save(&new_cfg)) {
      response_send("<mh#net#ok#restarting#end>");
      buzzer_beep_stop();
      watchdog_reboot(0, 0, 100);
      return;
    }
  }

  response_send("<mh#net#error#invalid_parameters#end>");
}

void net_command_handle_set_sta(const char *cmd_str) {
  nvm_wifi_config_t new_cfg;
  memset(&new_cfg, 0, sizeof(nvm_wifi_config_t));
  new_cfg.mode = (uint8_t)WIFI_MODE_STA;

  char ssid[NVM_SSID_MAX_LEN] = {0};
  char pass[NVM_PASS_MAX_LEN] = {0};
  uint32_t port = 0;

  if (sscanf(
          cmd_str, "mh#net#set#sta#%31[^#]#%63[^#]#%u#end", ssid, pass, &port
      ) == 3) {
    strncpy(new_cfg.ssid, ssid, sizeof(new_cfg.ssid) - 1);
    strncpy(new_cfg.password, pass, sizeof(new_cfg.password) - 1);
    new_cfg.port = (uint16_t)port;

    if (nvm_config_save(&new_cfg)) {
      response_send("<mh#net#ok#restarting#end>");
      buzzer_beep_stop();
      watchdog_reboot(0, 0, 100);
      return;
    }
  }

  response_send("<mh#net#error#invalid_parameters#end>");
}

void net_command_handle_reset(const char *cmd_str) {
  (void)cmd_str;
  if (nvm_config_reset_to_default()) {
    response_send("<mh#net#ok#default_restored#end>");
    buzzer_beep_stop();
    watchdog_reboot(0, 0, 100);
  } else {
    response_send("<mh#net#error#reset_failed#end>");
  }
}
