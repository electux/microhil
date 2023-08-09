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

#include <cstdint>
#include <vector>

using namespace std;

class AbMicroHILCom
{
public:
    ////////////////////////////////////////////////////////////////////////
    // AbMicroHILCom destructor
    virtual ~AbMicroHILCom() = default;

    ////////////////////////////////////////////////////////////////////////
    // Open communication channel
    virtual void open() = 0;
    
    ////////////////////////////////////////////////////////////////////////
    // Close communication channel
    virtual void close() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Read from communication channel
    virtual void read(
        std::vector<uint8_t>& dataBuffer, size_t len, size_t timeout
    ) = 0;

    ////////////////////////////////////////////////////////////////////////
    // Write to communication channel
    virtual void write(std::vector<uint8_t>& dataBuffer) = 0;
};
