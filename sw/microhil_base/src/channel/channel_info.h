/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_info.h
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
#pragma once

////////////////////////////////////////////////////////////////////////////
/// @brief Prefix info message for channel modules
#define MICROHIL_CHANNEL_INFO "[microHIL] INFO"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for initialization done
#define MICROHIL_INIT_DONE "initialization done"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for all channels ON
#define MICROHIL_ALL_ON "all channels on"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for all channels OFF
#define MICROHIL_ALL_OFF "all channels off"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for successs stdio initialization
#define MICROHIL_STDIO_DONE "stdio init done"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for successs usb initialization
#define MICROHIL_USB_DONE "usb init done"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for successs relay interface initialization
#define MICROHIL_RELAY_DONE "relay init done"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for successs pio interface initialization
#define MICROHIL_PIO_DONE "pio init done"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for successs buzzer interface initialization
#define MICROHIL_BUZZER_DONE "buzzer init done"
