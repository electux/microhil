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

class MicroHILViewSerial : public AbMicroHILViewSerial, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewSerial constructor
    MicroHILViewSerial(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewSerial destructor
    ~MicroHILViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial device file path input
    serialDevicePath serialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing Serial file path input 
    void onserialFilePathChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial baud rate combobox
    serialBaudRate serialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing Serial baud rate from combobox
    void onSerialBaudRateChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial data bits combobox
    serialDataBits serialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing Serial data bits combobox
    void onSerialDataBitsChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial parity combobox
    serialParity serialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing Serial parity combobox
    void onSerialParityChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial stop bits combobox
    serialStopBits serialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing Serial stop bits combobox
    void onSerialStopBitsChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from Serial Cancel and Ok buttons
    cancelSerial cancelSerialChanged() final;
    okSerial okSerialChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing Serial Cancel and Ok buttons
    void onCancelSerialChange() final;
    void onOkSerialChange() final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Map all signals and slots for serial dialog
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    // UI builder
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    // Widgets for serial view
    Glib::RefPtr<Gtk::Entry> m_device;
    Glib::RefPtr<Gtk::ComboBoxText> m_baudRate;
    Glib::RefPtr<Gtk::ComboBoxText> m_dataBits;
    Glib::RefPtr<Gtk::ComboBoxText> m_parity;
    Glib::RefPtr<Gtk::ComboBoxText> m_stopBits;
    Glib::RefPtr<Gtk::Button> m_cancel;
    Glib::RefPtr<Gtk::Button> m_ok;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial device path input
    serialDevicePath m_serialDevicePath;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial baud rate combobox
    serialBaudRate m_serialBaudeRate;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial data bits combobox
    serialDataBits m_serialDataBits;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial parity combobox
    serialParity m_serialParity;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Serial stop bits combobox
    serialStopBits m_serialStopBits;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from Cancel and Ok button (dismiss and confirm)
    cancelSerial m_cancelSerial;
    okSerial m_okSerial;
};
