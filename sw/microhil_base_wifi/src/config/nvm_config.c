/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * nvm_config.c
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
#include "nvm_config.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <string.h>

#define NVM_MAGIC 0x4D48494CU // 'MHIL'
#define NVM_VERSION 1U

#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
#define FLASH_TARGET_CONTENTS ((const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET))

static uint32_t calculate_checksum(const nvm_wifi_config_t *cfg) {
  const uint8_t *ptr = (const uint8_t *)cfg;
  size_t len = sizeof(nvm_wifi_config_t) - sizeof(uint32_t);
  uint32_t sum = 0x55AA55AAU;

  for (size_t i = 0; i < len; i++) {
    sum = ((sum << 5) + sum) + ptr[i];
  }

  return sum;
}

void nvm_config_get_default(nvm_wifi_config_t *config) {
  if (config == 0) {
    return;
  }

  memset(config, 0, sizeof(nvm_wifi_config_t));
  config->magic = NVM_MAGIC;
  config->version = NVM_VERSION;
  config->mode = (uint8_t)DEFAULT_WIFI_MODE;
  strncpy(config->ssid, DEFAULT_WIFI_SSID, NVM_SSID_MAX_LEN - 1);
  strncpy(config->password, DEFAULT_WIFI_PASSWORD, NVM_PASS_MAX_LEN - 1);
  strncpy(config->ip, DEFAULT_WIFI_IP, NVM_IP_MAX_LEN - 1);
  config->port = DEFAULT_WIFI_PORT;
  config->checksum = calculate_checksum(config);
}

void nvm_config_init(nvm_wifi_config_t *config) {
  if (config == 0) {
    return;
  }

  const nvm_wifi_config_t *flash_cfg =
      (const nvm_wifi_config_t *)FLASH_TARGET_CONTENTS;

  if (flash_cfg->magic == NVM_MAGIC && flash_cfg->version == NVM_VERSION) {
    uint32_t expected_crc = calculate_checksum(flash_cfg);
    if (flash_cfg->checksum == expected_crc) {
      memcpy(config, flash_cfg, sizeof(nvm_wifi_config_t));
      return;
    }
  }

  nvm_config_get_default(config);
}

bool nvm_config_save(const nvm_wifi_config_t *config) {
  if (config == 0) {
    return false;
  }

  uint8_t page_buffer[FLASH_PAGE_SIZE];
  memset(page_buffer, 0xFF, FLASH_PAGE_SIZE);

  nvm_wifi_config_t cfg_to_write;
  memcpy(&cfg_to_write, config, sizeof(nvm_wifi_config_t));
  cfg_to_write.magic = NVM_MAGIC;
  cfg_to_write.version = NVM_VERSION;
  cfg_to_write.checksum = calculate_checksum(&cfg_to_write);

  memcpy(page_buffer, &cfg_to_write, sizeof(nvm_wifi_config_t));

  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
  flash_range_program(FLASH_TARGET_OFFSET, page_buffer, FLASH_PAGE_SIZE);
  restore_interrupts(ints);

  return true;
}

bool nvm_config_reset_to_default(void) {
  nvm_wifi_config_t def_cfg;
  nvm_config_get_default(&def_cfg);
  return nvm_config_save(&def_cfg);
}
