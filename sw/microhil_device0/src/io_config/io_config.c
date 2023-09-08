/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_config.c
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
#include "io_config_info.h"
#include "io_config_error.h"
#include "io_config.h"

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_rst_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_dc_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_cs_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_bl_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_clk_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_mosi_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_scl_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
int epd_sda_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief TODO
uint slice_num;

////////////////////////////////////////////////////////////////////////////
/// @brief Setting port pin configuration
/// @param pin is GPIO pin number
/// @param mode is GPIO pin direction (GPIO_IN | GPIO_OUT)
void microhil_gpio_mode(uint16_t pin, uint16_t mode)
{
    gpio_init(pin);

    if (mode == 0 || mode == GPIO_IN)
    {
        gpio_set_dir(pin, GPIO_IN);
    }
    else
    {
        gpio_set_dir(pin, GPIO_OUT);
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Drive GPIO pin
/// @param pin is GPIO number
/// @param value is GPIO value (true - set | false - clear)
void microhil_digital_write(uint16_t pin, uint8_t value)
{
    gpio_put(pin, value);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Get GPIO state
/// @param pin is GPIO pin number
/// @return state of GPIO pin
uint8_t microhil_digital_read(uint16_t pin)
{
    return gpio_get(pin);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Write byte to an SPI device (blocking)
/// @param value is byte for write
void microhil_spi_write_byte(uint8_t value)
{
    spi_write_blocking(MICROHIL_SPI_PORT_1, &value, 1);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Write n bytes to an SPI device (blocking)
/// @param data is buffer for write
/// @param len is length of buffer to write
void microhil_spi_write_n_bytes(uint8_t *data, uint32_t len)
{
    spi_write_blocking(MICROHIL_SPI_PORT_1, data, len);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Send byte to i2c device
/// @param addr is address of device
/// @param reg is register destination
/// @param value is byte to send
void microhil_i2c_write_byte(uint8_t addr, uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};

    i2c_write_blocking(MICROHIL_I2C_PORT_1, addr, data, 2, false);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Send n bytes to i2c device
/// @param addr is address of device
/// @param data to send
/// @param len is length of data to send
void microhil_i2c_write_n_bytes(uint8_t addr, uint8_t *data, uint32_t len)
{
    i2c_write_blocking(MICROHIL_I2C_PORT_1, addr, data, len, false);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Read byte from i2c bus device
/// @param addr is address of device
/// @param reg is data to send
/// @return byte from i2c device
uint8_t microhil_i2c_read_byte(uint8_t addr, uint8_t reg)
{
    uint8_t buffer;

    i2c_write_blocking(MICROHIL_I2C_PORT_1, addr, &reg, 1, true);
    i2c_read_blocking(MICROHIL_I2C_PORT_1, addr, &buffer, 1, false);

    return buffer;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in miliseconds
/// @param ms is number of miliseconds to sleep
void microhil_delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in microseconds
/// @param us is number of microseconds to sleep
void microhil_delay_us(uint32_t us)
{
    sleep_us(us);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Private function for initialization reserved pins
void microhil_gpio_init()
{
    microhil_gpio_mode(epd_rst_pin, 1);
    microhil_gpio_mode(epd_dc_pin, 1);
    microhil_gpio_mode(epd_cs_pin, 1);
    microhil_gpio_mode(epd_bl_pin, 1);
    microhil_gpio_mode(epd_cs_pin, 1);
    microhil_gpio_mode(epd_bl_pin, 1);

    microhil_digital_write(epd_cs_pin, 1);
    microhil_digital_write(epd_dc_pin, 0);
    microhil_digital_write(epd_bl_pin, 1);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Set the current PWM counter compare value for one channel
/// @param value is new value for selected output
void microhil_set_pwm_1(uint8_t value)
{
    if (value < 0 || value > 100)
    {
        printf("%s %s\n", MICROHIL_IO_CONFIG_ERROR, MICROHIL_PWM_SET_ERROR);
    }
    else
    {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, value);
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief PWM, I2C, SPI modules initialization
/// @return true for success else false
bool microhil_module_init()
{
    bool status = false;

    status = stdio_init_all();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for stdio types
        return status;
    }

    epd_rst_pin = 12;
    epd_dc_pin = 8;
    epd_bl_pin = 6;
    epd_cs_pin = 9;
    epd_clk_pin = 10;
    epd_mosi_pin = 11;
    epd_scl_pin = 7;
    epd_sda_pin = 6;

    spi_init(MICROHIL_SPI_PORT_1, 1000 * 1000);
    gpio_set_function(epd_clk_pin, GPIO_FUNC_SPI);
    gpio_set_function(epd_mosi_pin, GPIO_FUNC_SPI);

    microhil_gpio_init();

    gpio_set_function(epd_bl_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(epd_bl_pin);
    pwm_set_wrap(slice_num, 100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);

    i2c_init(MICROHIL_I2C_PORT_1, 100 * 1000);
    gpio_set_function(epd_sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(epd_scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(epd_sda_pin);
    gpio_pull_up(epd_scl_pin);

    printf("%s %s\n", MICROHIL_IO_CONFIG_INFO, MICROHIL_MODULE_INIT_OK);

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Perform actions on exit
/// @return true for success else false
bool microhil_module_exit()
{
    return true;
}
