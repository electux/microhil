/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_config.h
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-device0 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-device0 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "stdio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"

////////////////////////////////////////////////////////////////////////////
/// @brief SPI instance
#define MICROHIL_SPI_PORT_1 spi1

////////////////////////////////////////////////////////////////////////////
/// @brief I2C instance
#define MICROHIL_I2C_PORT_1 i2c1

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_rst_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_dc_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_cs_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_bl_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_clk_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_mosi_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_scl_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern int epd_sda_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
extern uint slice_num;

////////////////////////////////////////////////////////////////////////////
/// @brief Setting port pin configuration
/// @param pin is GPIO pin number
/// @param mode is GPIO pin direction (GPIO_IN | GPIO_OUT)
void microhil_gpio_mode(uint16_t pin, uint16_t mode);

////////////////////////////////////////////////////////////////////////////
/// @brief Drive GPIO pin
/// @param pin is GPIO number
/// @param value is GPIO value (true - set | false - clear)
void microhil_digital_write(uint16_t pin, uint8_t value);

////////////////////////////////////////////////////////////////////////////
/// @brief Get GPIO state
/// @param pin is GPIO pin number
/// @return state of GPIO pin
uint8_t microhil_digital_read(uint16_t pin);

////////////////////////////////////////////////////////////////////////////
/// @brief Write byte to an SPI device (blocking)
/// @param value is byte for write
void microhil_spi_write_byte(uint8_t value);

////////////////////////////////////////////////////////////////////////////
/// @brief Write n bytes to an SPI device (blocking)
/// @param data is buffer for write
/// @param len is length of buffer to write
void microhil_spi_write_n_bytes(uint8_t *data, uint32_t len);

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in miliseconds
/// @param ms is number of miliseconds to sleep
void microhil_delay_ms(uint32_t ms);

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in microseconds
/// @param us is number of microseconds to sleep
void microhil_delay_us(uint32_t us);

////////////////////////////////////////////////////////////////////////////
/// @brief Send data to i2c device
/// @param addr is address of device
/// @param reg is register destination
/// @param value is data to send
void microhil_i2c_write_byte(uint8_t addr, uint8_t reg, uint8_t value);

////////////////////////////////////////////////////////////////////////////
/// @brief Send n bytes to i2c device
/// @param addr is address of device
/// @param data to send
/// @param len is length of data to send
void microhil_i2c_write_n_bytes(uint8_t addr, uint8_t *data, uint32_t len);

////////////////////////////////////////////////////////////////////////////
/// @brief Read byte from i2c bus device
/// @param addr is address of device
/// @param reg is data to send
/// @return byte from i2c device
uint8_t microhil_i2c_read_byte(uint8_t addr, uint8_t reg);

////////////////////////////////////////////////////////////////////////////
/// @brief Set the current PWM counter compare value for one channel
/// @param value is new value for selected output
void microhil_set_pwm_1(uint8_t value);

////////////////////////////////////////////////////////////////////////////
/// @brief PWM, I2C, SPI modules initialization
/// @return true for success else false
bool microhil_module_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Perform actions on exit
/// @return true for success else false
bool microhil_module_exit();
