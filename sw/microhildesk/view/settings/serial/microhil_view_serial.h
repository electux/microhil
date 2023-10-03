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
/// @brief MHViewSerial class is implementation of serial settings view
class MHViewSerial : public AbMHViewSerial, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewSerial constructor
    /// @param object repreesnts base object instance
    /// @param ui repreesnts buider instance
    MHViewSerial(BaseObjectType *object, MHRPtr<Gtk::Builder> const &ui);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewSerial destructor
    inline ~MHViewSerial() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for serial settings
    /// @return Signal for changed serial settings
    SigSerialSetup serialSetupChanged() final;

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
    /// @brief Sets loaded parameters for serial settings view
    /// @param device represents device absolute path for the serial device
    /// @param params represents parameters for the serial port parameters
    void serialSettingsLoaded(MHString &device, MHVecUInt &params);

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps all widgets (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    MHRPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Entry device file path
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
    /// @brief Signal for the serial settings
    SigSerialSetup m_serialSetup{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button (dismiss)
    SigCancelSerial m_cancelSerial{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (confirm)
    SigOkSerial m_okSerial{};
};
