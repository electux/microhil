#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define PICO_ERROR_TIMEOUT -1

#ifdef __cplusplus
extern "C" {
#endif

int getchar_timeout_us(uint32_t timeout_us);

#ifdef __cplusplus
}
#endif
