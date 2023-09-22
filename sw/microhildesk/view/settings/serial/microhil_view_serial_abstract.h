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

////////////////////////////////////////////////////////////////////////////
/// @brief AbMHViewSerial class declaration and definition
class AbMHViewSerial
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial settings
    using SigSerialSetup = sigc::signal<void(MHString&, MHVecUInt&)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial device file path input
    using SigSerialDevicePath = sigc::signal<void(MHString&)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial baud rate combobox
    using SigSerialBaudRate = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial data bits combobox
    using SigSerialDataBits = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial parity combobox
    using SigSerialParity = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial stop bits combobox
    using SigSerialStopBits = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Cancel button
    using SigCancelSerial = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Ok button
    using SigOkSerial = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMHViewLog destructor
    virtual ~AbMHViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for serial settings
    /// @return Signal for changed serial settings
    virtual SigSerialSetup serialSetupChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for device file path input
    /// @return Signal for changed device file path entry
    virtual SigSerialDevicePath serialFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing device file path input
    virtual void onSerialFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for baud rate combobox
    /// @return Signal for selected baud rate combobox
    virtual SigSerialBaudRate serialBaudRateChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing baud rate combobox
    virtual void onSerialBaudRateChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for data bits combobox
    /// @return Signal for selected data bits combobox
    virtual SigSerialDataBits serialDataBitsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing data bits combobox
    virtual void onSerialDataBitsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for parity combobox
    /// @return Signal for selected parity combobox
    virtual SigSerialParity serialParityChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing parity combobox
    virtual void onSerialParityChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for stop bits combobox
    /// @return Signal for selected stop bits combobox
    virtual SigSerialStopBits serialStopBitsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing stop bits combobox
    virtual void onSerialStopBitsChanged() = 0;

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
