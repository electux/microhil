/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial.h
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

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/dialog.h>
#include "microhil_view_serial_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILViewSerial class declaration and definition 
class MicroHILViewSerial: public AbMicroHILViewSerial, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewSerial constructor
    /// @param object base object instance
    /// @param ui buider parser
    MicroHILViewSerial(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewSerial destructor
    ~MicroHILViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from device file path input
    /// @return Signal after pefrormed action
    serialDevicePath serialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial file path input 
    void onserialFilePathChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial baud rate combobox
    /// @return Signal after pefrormed action
    serialBaudRate serialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial baud rate from combobox
    void onSerialBaudRateChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial data bits combobox
    /// @return Signal after pefrormed action
    serialDataBits serialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial data bits combobox
    void onSerialDataBitsChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial parity combobox
    /// @return Signal after pefrormed action
    serialParity serialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial parity combobox
    void onSerialParityChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial stop bits combobox
    /// @return Signal after pefrormed action
    serialStopBits serialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial stop bits combobox
    void onSerialStopBitsChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial Cancel button
    /// @return Signal after pefrormed action
    cancelSerial cancelSerialChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial Ok button
    /// @return Signal after pefrormed action
    okSerial okSerialChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button
    void onCancelSerialChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button
    void onOkSerialChange() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map all signals and slots for serial dialog
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set device file path
    Glib::RefPtr<Gtk::Entry> m_device;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select baud rate
    Glib::RefPtr<Gtk::ComboBoxText> m_baudRate;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select data bits
    Glib::RefPtr<Gtk::ComboBoxText> m_dataBits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select parity
    Glib::RefPtr<Gtk::ComboBoxText> m_parity;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select stop bits
    Glib::RefPtr<Gtk::ComboBoxText> m_stopBits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dismiss button
    Glib::RefPtr<Gtk::Button> m_cancel;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    Glib::RefPtr<Gtk::Button> m_ok;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial device path input
    serialDevicePath m_serialDevicePath;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial baud rate combobox
    serialBaudRate m_serialBaudeRate;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial data bits combobox
    serialDataBits m_serialDataBits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial parity combobox
    serialParity m_serialParity;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Serial stop bits combobox
    serialStopBits m_serialStopBits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Cancel button (dismiss)
    cancelSerial m_cancelSerial;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Ok button (confirm)
    okSerial m_okSerial;
};
