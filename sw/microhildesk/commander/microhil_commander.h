/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_commander.h
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

#include "../com/microhil_serial_com.h"
#include "microhil_icommander.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHCommander class is implementation of command mechanism
class MHCommander : public IMHCommander
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHCommander constructor
    explicit MHCommander(SPtr<IMHCom> serial);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHCommander destructor
    inline ~MHCommander() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Executes microHIL command
    /// @param id represents command identification
    /// @param onoff represents command operation
    void executeCommand(const int id, const std::string &onoff) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets identification of microHIL HW
    void getId();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets version of microHIL FW
    void getVersion();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets channel state
    /// @param id represents command identification
    /// @param onoff represents command operation
    void setChannel(const int id, const std::string &onoff);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets all channels
    /// @param onoff represents command operation
    void setAllChannel(const std::string &onoff);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    SPtr<IMHCom> m_serial{nullptr};
};
