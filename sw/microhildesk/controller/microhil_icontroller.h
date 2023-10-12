/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_icontroller.h
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
/// @brief IMHController class is interface set for controller
class IMHController
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHController destructor
    inline virtual ~IMHController() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enables controller (enable/disable communication)
    /// @param switchController represents requested enable value
    virtual void setEnabled(bool switchController) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks is controller enabled (is serial communication enabled)
    /// @return status true for enabled else false
    virtual bool isEnabled() const = 0;

protected:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps views and backend (signals and slots)
    virtual void mapping() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings changes
    /// @param path represents absolute path of log file
    /// @param level represents level for logging messages
    virtual void onLogSettingsChanged(UString &path, int level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings loaded
    /// @param path represents absolute path of log file
    /// @param logLevel represents level for logging messages
    virtual void onLogSettingsLoaded(UString &path, int level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev represents file path for serial device
    /// @param params represents set of serial parameters
    virtual void onSerialSettingsChanged(UString &dev, VecUInt &params) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev represents file path for serial device
    /// @param params represents set of serial parameters
    virtual void onSerialSettingsLoaded(UString &dev, VecUInt &params) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial port changes
    /// @param state true for enable port, else false
    virtual void onSerialControlChanged(bool state) = 0;
};
