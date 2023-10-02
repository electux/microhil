/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_iview.h
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

#include "home/microhil_view_home.h"
#include "settings/log/microhil_view_log.h"
#include "settings/serial/microhil_view_serial.h"
#include "../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for enable/disable serial communication channel
using SigSerialControl = sigc::signal<void(bool)>;

////////////////////////////////////////////////////////////////////////////
/// @brief IMHView class is interface set for view
class IMHView
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHView destructor
    virtual ~IMHView() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for controling serial port
    /// @return Signal for clicked Connect/Disconnect
    virtual SigSerialControl serialControlChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets home view
    /// @return Home view instance
    virtual MHRPtr<MHViewHome> getHome() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log settings view
    /// @return Log view settings instance
    virtual MHRPtr<MHViewLog> getLogSettings() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets serial settings view
    /// @return Serial view settings instance
    virtual MHRPtr<MHViewSerial> getSerialSettings() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps views (signal and slots)
    virtual void mapping() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing requests for triggering view
    /// @param id represents id of requested view
    virtual void onViewChanged(ViewId id) = 0;
};
