/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * nvm_config.c
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

#include "nvm_config.h"
#include "ble_default_config.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <string.h>

#define FLASH_CONFIG_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
#define FLASH_CONFIG_TARGET ((const uint8_t *)(XIP_BASE + FLASH_CONFIG_OFFSET))

static nvm_ble_config_t current_config;

static uint16_t calculate_checksum(const nvm_ble_config_t *cfg) {
  const uint8_t *data = (const uint8_t *)cfg;
  size_t len = sizeof(nvm_ble_config_t) - sizeof(uint16_t);
  uint16_t sum = 0;
  for (size_t i = 0; i < len; i++) {
    sum += data[i];
  }
  return sum;
}

static void load_defaults(nvm_ble_config_t *cfg) {
  memset(cfg, 0, sizeof(nvm_ble_config_t));
  cfg->magic = NVM_BLE_MAGIC;
  cfg->version = NVM_BLE_CONFIG_VERSION;
  strncpy(
      cfg->device_name, DEFAULT_BLE_DEVICE_NAME,
      sizeof(cfg->device_name) - 1
  );
  cfg->adv_interval_ms = DEFAULT_BLE_ADV_INTERVAL_MS;
  cfg->passkey = DEFAULT_BLE_PASSKEY;
  cfg->checksum = calculate_checksum(cfg);
}

bool nvm_config_init(void) {
  const nvm_ble_config_t *flash_cfg =
      (const nvm_ble_config_t *)FLASH_CONFIG_TARGET;

  if (flash_cfg->magic == NVM_BLE_MAGIC &&
      flash_cfg->version == NVM_BLE_CONFIG_VERSION) {
    uint16_t expected_sum = calculate_checksum(flash_cfg);
    if (flash_cfg->checksum == expected_sum) {
      memcpy(&current_config, flash_cfg, sizeof(nvm_ble_config_t));
      return true;
    }
  }

  load_defaults(&current_config);
  return false;
}

const nvm_ble_config_t *nvm_config_get(void) {
  return &current_config;
}

bool nvm_config_save(const nvm_ble_config_t *new_cfg) {
  uint8_t buffer[FLASH_PAGE_SIZE];
  memset(buffer, 0xFF, sizeof(buffer));

  nvm_ble_config_t cfg_to_write;
  memcpy(&cfg_to_write, new_cfg, sizeof(nvm_ble_config_t));
  cfg_to_write.magic = NVM_BLE_MAGIC;
  cfg_to_write.version = NVM_BLE_CONFIG_VERSION;
  cfg_to_write.checksum = calculate_checksum(&cfg_to_write);

  memcpy(buffer, &cfg_to_write, sizeof(nvm_ble_config_t));

  uint32_t ints = save_and_disable_interrupts();
  flash_range_erase(FLASH_CONFIG_OFFSET, FLASH_SECTOR_SIZE);
  flash_range_program(FLASH_CONFIG_OFFSET, buffer, FLASH_PAGE_SIZE);
  restore_interrupts(ints);

  return nvm_config_init();
}

bool nvm_config_reset_to_default(void) {
  nvm_ble_config_t def_cfg;
  load_defaults(&def_cfg);
  return nvm_config_save(&def_cfg);
}
