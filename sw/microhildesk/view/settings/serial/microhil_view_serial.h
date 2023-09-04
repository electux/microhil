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
        BaseObjectType* object, MHRPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewSerial destructor
    ~MicroHILViewSerial() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for serial settings
    /// @return Signal for changed serial settings
    SigSerialSetup serialSetupChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for device file path input
    /// @return Signal for changed device file path entry
    SigSerialDevicePath serialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing device file path input
    void onSerialFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for baud-rate combobox
    /// @return Signal for selected baud-rate combobox
    SigSerialBaudRate serialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing baud-rate combobox
    void onSerialBaudRateChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for data-bits combobox
    /// @return Signal for selected data-bits combobox
    SigSerialDataBits serialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing data-bits combobox
    void onSerialDataBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for parity combobox
    /// @return Signal for selected parity combobox
    SigSerialParity serialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing parity combobox
    void onSerialParityChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for stop-bits combobox
    /// @return Signal for selected stop-bits combobox
    SigSerialStopBits serialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing stop-bits combobox
    void onSerialStopBitsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    SigCancelSerial cancelSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    SigOkSerial okSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button (dismiss)
    void onCancelSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (confirm)
    void onOkSerialTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set loaded parameters for serial settings view
    /// @param device is absolute path for serial device
    /// @param params for serial port parameters
    void serialSettingsLoaded(MHString device, MHVecUInt params);

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map all widgets (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    MHRPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set device file path
    MHRPtr<Gtk::Entry> m_device{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select baud-rate
    MHRPtr<Gtk::ComboBoxText> m_baudRate{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select data-bits
    MHRPtr<Gtk::ComboBoxText> m_dataBits{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select parity
    MHRPtr<Gtk::ComboBoxText> m_parity{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Select stop-bits
    MHRPtr<Gtk::ComboBoxText> m_stopBits{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dismiss button
    MHRPtr<Gtk::Button> m_cancel{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    MHRPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief ignal for serial settings
    SigSerialSetup m_serialSetup{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for device path input
    SigSerialDevicePath m_serialDevicePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for baud-rate combobox
    SigSerialBaudRate m_serialBaudeRate{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for data-bits combobox
    SigSerialDataBits m_serialDataBits{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for parity combobox
    SigSerialParity m_serialParity{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for stop-bits combobox
    SigSerialStopBits m_serialStopBits{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button (dismiss)
    SigCancelSerial m_cancelSerial{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (confirm)
    SigOkSerial m_okSerial{};
};
