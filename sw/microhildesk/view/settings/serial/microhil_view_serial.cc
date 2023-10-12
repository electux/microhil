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
    /// Combobox id for selecting baud-rate
    constexpr const char kBaudRateSelectorId[]{"SerialPortBaudRateSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting data-bits
    constexpr const char kDataBitsSelectorId[]{"SerialPortDataBitsSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting parity
    constexpr const char kParitySelectorId[]{"SerialPortParitySelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Combobox id for selecting stop-bits
    constexpr const char kStopBitsId[]{"SerialPortStopBitsSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// Cancel button id
    constexpr const char kCancelButtonId[]{"SerialCancel"};

    ////////////////////////////////////////////////////////////////////////
    /// Ok button id
    constexpr const char kOkButtonId[]{"SerialOk"};
} // namespace

MHViewSerial::MHViewSerial(BaseObjectType *object, RPtr<Gtk::Builder> const &ui)
    : Gtk::Dialog(object)
    , m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    /// Binds Log file path entry
    m_device = RPtr<Gtk::Entry>::cast_dynamic(m_ui->get_object(kDevicePathId));

    ////////////////////////////////////////////////////////////////////////
    /// Binds baud-rate combobox
    m_baudRate = RPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kBaudRateSelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Binds data-bits combobox
    m_dataBits = RPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kDataBitsSelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Binds parity combobox
    m_parity = RPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kParitySelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Binds stop-bits combobox
    m_stopBits =
        RPtr<Gtk::ComboBoxText>::cast_dynamic(m_ui->get_object(kStopBitsId));

    ////////////////////////////////////////////////////////////////////////
    /// Binds Cancel button
    m_cancel =
        RPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kCancelButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Binds Ok button
    m_ok = RPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kOkButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Maps all widgets (signals and slots)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Hides Serial Settings by default
    this->hide();
}

void MHViewSerial::serialSettingsLoaded(UString &device, VecUInt &params)
{
    m_device->set_text(device);
    m_baudRate->set_active(params[0]);
    m_dataBits->set_active(params[1]);
    m_parity->set_active(params[2]);
    m_stopBits->set_active(params[3]);
}
