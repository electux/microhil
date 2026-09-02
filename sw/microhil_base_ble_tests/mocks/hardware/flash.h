#pragma once
#include <stdint.h>
#include <stddef.h>

#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#define FLASH_SECTOR_SIZE 4096
#define FLASH_PAGE_SIZE 256

extern uint8_t mock_flash_storage[PICO_FLASH_SIZE_BYTES];
#define XIP_BASE ((uintptr_t)mock_flash_storage)

#ifdef __cplusplus
extern "C" {
#endif

void flash_range_erase(uint32_t offset, size_t count);
void flash_range_program(uint32_t offset, const uint8_t *data, size_t count);

#ifdef __cplusplus
}
#endif
