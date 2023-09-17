/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_uart.c
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <string.h>
#include "channel_error.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Fetch microHIL command messages from the serial port
/// @param buffer storage for received message from the serial port
/// @return number of received bytes from the serial port
uint16_t microhil_fetch_command(uint8_t *buffer)
{
    uint16_t buffer_index = 0;

    while (true)
    {
        int byte = getchar_timeout_us(100);

        if (byte != PICO_ERROR_TIMEOUT && buffer_index < MICROHIL_CMD_LEN)
        {
            buffer[buffer_index++] = (byte & 0xFF);
        }
        else
        {
            buffer[buffer_index] = 0;
            break;
        }
    }

    return buffer_index;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Extract command property (private)
/// @param cmd is whole command messsage for processing
/// @return command property
unsigned char *microhil_extract_command_property(unsigned char *cmd)
{
    int cmd_len = strlen(cmd);
    int prefix_len = strlen(MICROHIL_CMD_PREFIX);
    int len = cmd_len - prefix_len;

    ////////////////////////////////////////////////////////////////////////
    /// Sanity check for expected command message prefix
    int status = strncmp(cmd, MICROHIL_CMD_PREFIX, prefix_len);

    if (status != 0)
    {
        ////////////////////////////////////////////////////////////////////
        /// Not matched expected command message prefix
        return NULL;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Extract command property
    unsigned char *cmd_property = (unsigned char *)malloc(len);
    sprintf(cmd_property, "%s", cmd + prefix_len);

    ////////////////////////////////////////////////////////////////////////
    /// Command message property (microHIL format)
    return cmd_property;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Process command property for all channels ON (private)
/// @param cmd_property instruction
/// @return command id for all channels ON
int microhil_process_all_on(unsigned char *cmd_property)
{
    int len = strlen(MICROHIL_CMD_PROP_ALL_ON);
    return strncmp(cmd_property, MICROHIL_CMD_PROP_ALL_ON, len);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Process command property for all channels OFF (private)
/// @param cmd_property instruction
/// @return command id for all channels OFF
int microhil_process_all_off(unsigned char *cmd_property)
{
    int len = strlen(MICROHIL_CMD_PROP_ALL_OFF);
    return strncmp(cmd_property, MICROHIL_CMD_PROP_ALL_OFF, len);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Process command property for channel (private)
/// @param cmd_property instruction
/// @param id for channel
/// @return command id for channel
int microhil_process_channel_on(unsigned char *cmd_property, int index)
{
    if (0 > index || index > MICROHIL_NUMBER_OF_CHANNELS)
    {
        return (int)MICROHIL_CHANNELS_ERROR;
    }

    char *operation_on = (char *)malloc(MICROHIL_PROP_ON_RESERVE);
    sprintf(operation_on, "%d#on", index);
    int status = strncmp(cmd_property, operation_on, strlen(operation_on));
    free(operation_on);

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Process command property for channel (private)
/// @param cmd_property instruction
/// @param id for channel
/// @return command id for channel
int microhil_process_channel_off(unsigned char *cmd_property, int index)
{
    if (0 > index || index > MICROHIL_NUMBER_OF_CHANNELS)
    {
        return (int)MICROHIL_CHANNELS_ERROR;
    }

    char *operation_off = (char *)malloc(MICROHIL_PROP_OFF_RESERVE);
    sprintf(operation_off, "%d#off", index);
    int status = strncmp(cmd_property, operation_off, strlen(operation_off));
    free(operation_off);

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Process microHIL command messages from uart
/// @param cmd is whole command for processing
/// @return GPIO port number
channel_gpio_num microhil_process_command(unsigned char *cmd)
{
    unsigned char *cmd_property = microhil_extract_command_property(cmd);

    if (cmd_property == NULL)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to extract command property
        printf("%s %s\n", MICROHIL_CHANNEL_ERROR, MICROHIL_EXT_PROP_FAILED);
        return MICROHIL_CHANNELS_ERROR;
    }

    if (microhil_process_all_on(cmd_property) == 0)
    {
        free(cmd_property);
        ////////////////////////////////////////////////////////////////////
        /// Request command all channels ON
        return MICROHIL_ALL_CHANNELS_ON;
    }

    if (microhil_process_all_off(cmd_property) == 0)
    {
        free(cmd_property);
        ////////////////////////////////////////////////////////////////////
        /// Request command all channels OFF
        return MICROHIL_ALL_CHANNELS_OFF;
    }

    for (int i = 0; i < MICROHIL_NUMBER_OF_CHANNELS; i++)
    {
        if (microhil_process_channel_on(cmd_property, i) == 0)
        {
            free(cmd_property);
            ////////////////////////////////////////////////////////////////
            /// Request command switch channel 1..8
            return index_to_gpio(i);
        }

        if (microhil_process_channel_off(cmd_property, i) == 0)
        {
            free(cmd_property);
            ////////////////////////////////////////////////////////////////
            /// Request command switch channel 1..8
            return index_to_gpio(i);
        }
    }

    free(cmd_property);
    ////////////////////////////////////////////////////////////////////
    /// Requested command not supported
    printf("%s %s\n", MICROHIL_CHANNEL_ERROR, MICROHIL_NO_SUPPORT);
    return MICROHIL_CHANNELS_ERROR;
}
