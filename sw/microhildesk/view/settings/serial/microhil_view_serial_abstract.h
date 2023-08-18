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

#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewSerial class declaration and definition 
class AbMicroHILViewSerial
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial device file path
    using serialDevicePath = sigc::signal<void(Glib::ustring)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for selectable serial baud rate
    using serialBaudRate = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for selectable serial data bits
    using serialDataBits = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for selectable serial parity
    using serialParity = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for selectable serial stop bits
    using serialStopBits = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Cancel button
    using cancelSerial = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Ok button
    using okSerial = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewLog destructor
    virtual ~AbMicroHILViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from device file path input
    /// @return Signal after pefrormed action
    virtual serialDevicePath serialFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial file path input 
    virtual void onserialFilePathChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial baud rate combobox
    /// @return Signal after pefrormed action
    virtual serialBaudRate serialBaudRateChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial baud rate from combobox
    virtual void onSerialBaudRateChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial data bits combobox
    /// @return Signal after pefrormed action
    virtual serialDataBits serialDataBitsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial data bits combobox
    virtual void onSerialDataBitsChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial parity combobox
    /// @return Signal after pefrormed action
    virtual serialParity serialParityChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial parity combobox
    virtual void onSerialParityChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial stop bits combobox
    /// @return Signal after pefrormed action
    virtual serialStopBits serialStopBitsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial stop bits combobox
    virtual void onSerialStopBitsChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial Cancel button
    /// @return Signal after pefrormed action
    virtual cancelSerial cancelSerialChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial Ok button
    /// @return Signal after pefrormed action
    virtual okSerial okSerialChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button
    virtual void onCancelSerialChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button
    virtual void onOkSerialChange() = 0;
};
