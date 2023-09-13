/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_com_abstract.h
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

#include "../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////////
/// @brief AbMHCom class declaration and definition
class AbMHCom
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMHCom destructor
    virtual ~AbMHCom() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Open communication channel
    virtual void open() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Close communication channel
    virtual void close() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Read from communication channel
    /// @param data buffer to be placed to after reading channel
    /// @param len length of data to read before returning
    /// @param timeout timeout period in miliseconds
    virtual void read(MHVecByte &data, size_t len, size_t timeout) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Write to communication channel
    /// @param data to be written to channel
    virtual void write(MHVecByte &data) = 0;
};
