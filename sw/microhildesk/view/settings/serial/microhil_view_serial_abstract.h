/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial_abstract.h
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

#include <sigc++/sigc++.h>
#include "../../../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for serial settings
using SigSerialSetup = sigc::signal<void(MHString &, MHVecUInt &)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for Cancel button
using SigCancelSerial = sigc::signal<void(bool)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for Ok button
using SigOkSerial = sigc::signal<void(bool)>;

////////////////////////////////////////////////////////////////////////////
/// @brief AbMHViewSerial class is abstract setup gfor serial settings view
class AbMHViewSerial
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMHViewLog destructor
    inline virtual ~AbMHViewSerial() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for serial settings
    /// @return Signal for changed serial settings
    virtual SigSerialSetup serialSetupChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    virtual SigCancelSerial cancelSerialTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    virtual SigOkSerial okSerialTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button (dismiss)
    virtual void onCancelSerialTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (confirm)
    virtual void onOkSerialTriggered() = 0;
};
