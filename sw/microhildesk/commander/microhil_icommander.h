/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_icommander.h
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <string>

////////////////////////////////////////////////////////////////////////////
/// @brief IMHCommander class is interface set for command mechanism
class IMHCommander
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHCommander destructor
    inline ~IMHCommander() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Executes microHIL command
    /// @param id represents command identification
    /// @param onoff represents command operation
    virtual void executeCommand(const int id, const std::string &onoff) = 0;
};
