/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel.c
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
#include "channel_info.h"
#include "channel_error.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Container for storing channels states
static unsigned char channels[MICROHIL_NUMBER_OF_CHANNELS];

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to ON
void microhil_all_channels_on()
{
    ////////////////////////////////////////////////////////////////////////
    /// Set relay channels to ON
    microhil_digital_write(MICROHIL_CHANNEL_7, true);
    microhil_digital_write(MICROHIL_CHANNEL_6, true);
    microhil_digital_write(MICROHIL_CHANNEL_5, true);
    microhil_digital_write(MICROHIL_CHANNEL_4, true);
    microhil_digital_write(MICROHIL_CHANNEL_3, true);
    microhil_digital_write(MICROHIL_CHANNEL_2, true);
    microhil_digital_write(MICROHIL_CHANNEL_1, true);
    microhil_digital_write(MICROHIL_CHANNEL_0, true);

    ////////////////////////////////////////////////////////////////////////
    /// Store channel states
    for(int i = 0; i < MICROHIL_NUMBER_OF_CHANNELS; i++)
    {
        channels[i] = 0x1;
    }

    printf("%s %s\n", MICROHIL_CHANNEL_INFO, MICROHIL_ALL_ON);

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    microhi_write_pixel(urgb_u32(255, 255, 255));

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_pwm(80, PWM_CHAN_A);
    microhil_delay_ms(100);
    microhil_write_pwm(0, PWM_CHAN_A);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to OFF
void microhil_all_channels_off()
{
    ////////////////////////////////////////////////////////////////////////
    /// Set relay channels to OFF
    microhil_digital_write(MICROHIL_CHANNEL_7, false);
    microhil_digital_write(MICROHIL_CHANNEL_6, false);
    microhil_digital_write(MICROHIL_CHANNEL_5, false);
    microhil_digital_write(MICROHIL_CHANNEL_4, false);
    microhil_digital_write(MICROHIL_CHANNEL_3, false);
    microhil_digital_write(MICROHIL_CHANNEL_2, false);
    microhil_digital_write(MICROHIL_CHANNEL_1, false);
    microhil_digital_write(MICROHIL_CHANNEL_0, false);

    ////////////////////////////////////////////////////////////////////////
    /// Store channel states
    for(int i = 0; i < MICROHIL_NUMBER_OF_CHANNELS; i++)
    {
        channels[i] = 0x0;
    }

    printf("%s %s\n", MICROHIL_CHANNEL_INFO, MICROHIL_ALL_OFF);

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    microhi_write_pixel(urgb_u32(0, 0, 0));

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_pwm(80, PWM_CHAN_A);
    microhil_delay_ms(100);
    microhil_write_pwm(0, PWM_CHAN_A);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Convert GPIO port number to index (private)
/// @param id GPIO port number for serial port
/// @return index of channel
unsigned int gpio_to_index(channel_gpio_num id)
{
    switch (id)
    {
        case MICROHIL_CHANNEL_0: return 0;
        case MICROHIL_CHANNEL_1: return 1;
        case MICROHIL_CHANNEL_2: return 2;
        case MICROHIL_CHANNEL_3: return 3;
        case MICROHIL_CHANNEL_4: return 4;
        case MICROHIL_CHANNEL_5: return 5;
        case MICROHIL_CHANNEL_6: return 6;
        case MICROHIL_CHANNEL_7: return 7;
    }

    return 127;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Switch channel state
/// @param id is GPIO port number
void microhil_channel_switch(channel_gpio_num gpio)
{
    switch(gpio)
    {
        case MICROHIL_ALL_CHANNELS_OFF:
            microhil_all_channels_off();
            break;
        case MICROHIL_ALL_CHANNELS_ON:
            microhil_all_channels_on();
            break;
        case MICROHIL_CHANNELS_ERROR:
            printf("%s %s\n", MICROHIL_CHANNEL_ERROR, MICROHIL_NO_SUPPORT);
            break;
        default:
            unsigned int index = gpio_to_index(gpio);

            if(index == MICROHIL_CHANNELS_ERROR)
            {
                printf("%s %s\n", MICROHIL_CHANNEL_ERROR, MICROHIL_NO_SUPPORT);
                break;
            }

            channels[index] = !channels[index];
            microhil_digital_write(gpio, (bool)channels[index]);

            if(channels[index] == 1)
            {
                printf("%s channel %d on\n", MICROHIL_CHANNEL_INFO, index);
            }
            else if(channels[index] == 0)
            {
                printf("%s channel %d off\n", MICROHIL_CHANNEL_INFO, index);
            }

            ////////////////////////////////////////////////////////////////
            /// Led notification
            microhi_write_pixel(urgb_u32(255, 0, 0));

            ////////////////////////////////////////////////////////////////
            /// Buzzer notification
            microhil_write_pwm(80, PWM_CHAN_A);
            microhil_delay_ms(100);
            microhil_write_pwm(0, PWM_CHAN_A);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Convert index to GPIO port number
/// @param id is index
/// @return GPIO port number
channel_gpio_num index_to_gpio(int id)
{
    switch(id)
    {
        case 0: return MICROHIL_CHANNEL_0;
        case 1: return MICROHIL_CHANNEL_1;
        case 2: return MICROHIL_CHANNEL_2;
        case 3: return MICROHIL_CHANNEL_3;
        case 4: return MICROHIL_CHANNEL_4;
        case 5: return MICROHIL_CHANNEL_5;
        case 6: return MICROHIL_CHANNEL_6;
        case 7: return MICROHIL_CHANNEL_7;
    }

    return MICROHIL_CHANNELS_ERROR;
}
