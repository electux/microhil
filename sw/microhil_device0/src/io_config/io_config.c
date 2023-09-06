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
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "io_config.h"

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_RST_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_DC_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_CS_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_BL_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_CLK_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_MOSI_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_SCL_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
int EPD_SDA_PIN;

////////////////////////////////////////////////////////////////////////////
/// @brief
uint slice_num;

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param pin
/// @param value
void microhil_digital_write(uint16_t pin, uint8_t value)
{
    gpio_put(pin, value);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param pin
/// @return
uint8_t microhil_digital_read(uint16_t pin)
{
    return gpio_get(pin);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param value
void microhil_spi_write_byte(uint8_t value)
{
    spi_write_blocking(SPI_PORT, &value, 1);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param data
/// @param len
void microhil_spi_write_n_bytes(uint8_t *data, uint32_t len)
{
    spi_write_blocking(SPI_PORT, data, len);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param addr
/// @param reg
/// @param value
void microhil_i2c_write_byte(uint8_t addr, uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};

    i2c_write_blocking(i2c1, addr, data, 2, false);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param addr
/// @param data
/// @param len
void microhil_i2c_write_n_bytes(uint8_t addr, uint8_t *data, uint32_t len)
{
    i2c_write_blocking(i2c1, addr, data, len, false);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param addr
/// @param reg
/// @return
uint8_t microhil_i2c_read_byte(uint8_t addr, uint8_t reg)
{
    uint8_t buf;

    i2c_write_blocking(i2c1, addr, &reg, 1, true);
    i2c_read_blocking(i2c1, addr, &buf, 1, false);

    return buf;
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param pin
/// @param mode
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
/// @brief
/// @param ms
void microhil_delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param us
void microhil_delay_us(uint32_t us)
{
    sleep_us(us);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
void microhil_gpio_init()
{
    microhil_gpio_mode(EPD_RST_PIN, 1);
    microhil_gpio_mode(EPD_DC_PIN, 1);
    microhil_gpio_mode(EPD_CS_PIN, 1);
    microhil_gpio_mode(EPD_BL_PIN, 1);
    microhil_gpio_mode(EPD_CS_PIN, 1);
    microhil_gpio_mode(EPD_BL_PIN, 1);
    microhil_digital_write(EPD_CS_PIN, 1);
    microhil_digital_write(EPD_DC_PIN, 0);
    microhil_digital_write(EPD_BL_PIN, 1);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @return
uint8_t microhil_module_init()
{
    stdio_init_all();

    EPD_RST_PIN = 12;
    EPD_DC_PIN = 8;
    EPD_BL_PIN = 6;
    EPD_CS_PIN = 9;
    EPD_CLK_PIN = 10;
    EPD_MOSI_PIN = 11;
    EPD_SCL_PIN = 7;
    EPD_SDA_PIN = 6;

    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(EPD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(EPD_MOSI_PIN, GPIO_FUNC_SPI);
    microhil_gpio_init();
    gpio_set_function(EPD_BL_PIN, GPIO_FUNC_PWM);

    slice_num = pwm_gpio_to_slice_num(EPD_BL_PIN);

    pwm_set_wrap(slice_num, 100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);
    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(EPD_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(EPD_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(EPD_SDA_PIN);
    gpio_pull_up(EPD_SCL_PIN);
    printf("microhil_module_init OK \r\n");

    return 0;
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param value
void microhil_set_pwm_1(uint8_t value)
{
    if (value < 0 || value > 100)
    {
        printf("microhil_write_pwm Error \r\n");
    }
    else
    {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, value);
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief
void microhil_module_exit()
{
}
