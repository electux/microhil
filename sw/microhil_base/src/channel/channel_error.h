/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_error.h
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
/// @brief Prefix error message for channel modules
#define MICROHIL_CHANNEL_ERROR "[microHIL] ERROR"

////////////////////////////////////////////////////////////////////////////
/// @brief Error message for initialization failed
#define MICROHIL_INIT_FAILED "initialization failed"

////////////////////////////////////////////////////////////////////////////
/// @brief Error message for not supported channel operation
#define MICROHIL_NO_SUPPORT "not supported channel operation"

////////////////////////////////////////////////////////////////////////////
/// @brief Error message for extracting property from command message
#define MICROHIL_EXT_PROP_FAILED "failed to extract property from message"
