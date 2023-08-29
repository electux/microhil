/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial.cc
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
#include "microhil_view_serial.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Entry id
    constexpr const char kDevicePathId[]{"SerialPortDeviceInput"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting baud rate
    constexpr const char kBaudRateSelectorId[]{"SerialPortBaudRateSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting data bits 
    constexpr const char kDataBitsSelectorId[]{"SerialPortDataBitsSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting parity
    constexpr const char kParitySelectorId[]{"SerialPortParitySelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting stop bits
    constexpr const char kStopBitsId[]{"SerialPortStopBitsSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Cancel button id
    constexpr const char kCancelButtonId[]{"SerialCancel"};

    ////////////////////////////////////////////////////////////////////////
    /// Ok button id
    constexpr const char kOkButtonId[]{"SerialOk"};
}

MicroHILViewSerial::MicroHILViewSerial(
    BaseObjectType *object, Glib::RefPtr<Gtk::Builder> const &ui
): Gtk::Dialog(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    /// Bind Log file path entry
    m_device = Glib::RefPtr<Gtk::Entry>::cast_dynamic(
        m_ui->get_object(kDevicePathId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind baud rate combobox
    m_baudRate = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kBaudRateSelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind data bits combobox
    m_dataBits = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kDataBitsSelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind parity combobox
    m_parity = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kParitySelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind stop bits combobox
    m_stopBits = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kStopBitsId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind Cancel button
    m_cancel = Glib::RefPtr<Gtk::Button>::cast_dynamic(
        m_ui->get_object(kCancelButtonId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Bind Ok button
    m_ok = Glib::RefPtr<Gtk::Button>::cast_dynamic(
        m_ui->get_object(kOkButtonId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map all widgets (signals and slots)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Hide Serial Settings by default
    this->hide();
}

void MicroHILViewSerial::serialSettingsLoaded(
    Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
    unsigned int parity, unsigned int stopBits)
{
    m_device->set_text(device);
    m_baudRate->set_active(baudRate);
    m_dataBits->set_active(dataBits);
    m_parity->set_active(parity);
    m_stopBits->set_active(stopBits);
}
