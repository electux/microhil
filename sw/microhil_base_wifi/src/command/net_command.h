/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * net_command.h
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-wifi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-wifi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Handles <mh#net#get#end> command
void net_command_handle_get(const char *cmd_str);

////////////////////////////////////////////////////////////////////////////
/// @brief Handles <mh#net#set#ap#...#end> command
void net_command_handle_set_ap(const char *cmd_str);

////////////////////////////////////////////////////////////////////////////
/// @brief Handles <mh#net#set#sta#...#end> command
void net_command_handle_set_sta(const char *cmd_str);

////////////////////////////////////////////////////////////////////////////
/// @brief Handles <mh#net#reset#end> command
void net_command_handle_reset(const char *cmd_str);

#ifdef __cplusplus
}
#endif
