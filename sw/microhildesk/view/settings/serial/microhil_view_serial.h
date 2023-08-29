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
    /// @param ui buider instance
    MicroHILViewSerial(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewSerial destructor
    ~MicroHILViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for serial settings
    /// @return Signal for changed serial settings
    serialSetup serialSetupChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for device file path input
    /// @return Signal for changed device file path entry
    serialDevicePath serialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing device file path input
    void onSerialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for baud rate combobox
    /// @return Signal for selected baud rate combobox
    serialBaudRate serialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing baud rate combobox
    void onSerialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for data bits combobox
    /// @return Signal for selected data bits combobox
    serialDataBits serialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing data bits combobox
    void onSerialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for parity combobox
    /// @return Signal for selected parity combobox
    serialParity serialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing parity combobox
    void onSerialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for stop bits combobox
    /// @return Signal for selected stop bits combobox
    serialStopBits serialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing stop bits combobox
    void onSerialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    cancelSerial cancelSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    okSerial okSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button (dismiss)
    void onCancelSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (confirm)
    void onOkSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set loaded parameters for serial settings view
    /// @param device is absolute path for serial device
    /// @param baudRate for serial port
    /// @param dataBits for serial port
    /// @param parity for serial port
    /// @param stopBits for serial port
    void serialSettingsLoaded(
        Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
        unsigned int parity, unsigned int stopBits
    );

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map all widgets (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set device file path
    Glib::RefPtr<Gtk::Entry> m_device{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select baud rate
    Glib::RefPtr<Gtk::ComboBoxText> m_baudRate{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select data bits
    Glib::RefPtr<Gtk::ComboBoxText> m_dataBits{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select parity
    Glib::RefPtr<Gtk::ComboBoxText> m_parity{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select stop bits
    Glib::RefPtr<Gtk::ComboBoxText> m_stopBits{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dismiss button
    Glib::RefPtr<Gtk::Button> m_cancel{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    Glib::RefPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief ignal for serial settings
    serialSetup m_serialSetup{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for device path input
    serialDevicePath m_serialDevicePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for baud rate combobox
    serialBaudRate m_serialBaudeRate{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for data bits combobox
    serialDataBits m_serialDataBits{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for parity combobox
    serialParity m_serialParity{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for stop bits combobox
    serialStopBits m_serialStopBits{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button (dismiss)
    cancelSerial m_cancelSerial{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (confirm)
    okSerial m_okSerial{};
};
