/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings.h
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <sigc++/sigc++.h>
#include "../settings_setup.h"

namespace Electux::App::View::Settings
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for serial settings
    using SigSetup = sigc::signal<void(SettingsSetup &)>;

    //////////////////////////////////////////////////////////////////////////
    /// @brief Application settings window definition
    class AppSettings : public Gtk::Window
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief AppSettings constructor
        explicit AppSettings();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal for serial settings
        /// @return Signal for changed serial settings
        SigSetup setupChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Sets configuration setup
        void setSettingsSetup(const SettingsSetup& setup);

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets UI data from widgets and saves them to configuration
        void getUiData();

        //////////////////////////////////////////////////////////////////////
        /// @brief Updates UI widgets with data from loaded configuration
        void updateUiData();

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Maps channels (signals and slots)
        void mapping();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action OK button
        void onButtonOkClicked();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action Cancel button
        void onButtonCancelClicked();

        //////////////////////////////////////////////////////////////////////
        /// @brief Container for packing widgets for settings window
        ///   m_setup - settings parameters container
        ///   m_setupSignal - signal for the serial settings changes
        ///   m_boxRoot - vertical box as root container box
        ///   m_notebook - notebook container for settings pages serial port and log
        ///   m_boxSerial - vertical box as container box for serial settings
        ///   m_labelSerialPath - serial path label
        ///   m_entrySerialPath - entry for serial device path
        ///   m_labelSerialBaud - serial baud rate label
        ///   m_comboSerialBaud - serial baud rate combobox
        ///   m_labelSerialData - serial data bits label
        ///   m_comboSerialData - serial data bits combobox
        ///   m_labelSerialParity - serial parity label
        ///   m_comboSerialParity - serial parity combobox
        ///   m_labelSerialStop - serial stop bits label
        ///   m_comboSerialStop - serial stop bits combobox
        ///   m_labelSerialFlowControl - serial flow control label
        ///   m_comboSerialFlowControl - serial flow control combobox
        ///   m_boxLog - vertical box as container box for log settings
        ///   m_labelLogPath - log path label 
        ///   m_entryLogPath - log file path entry
        ///   m_labelLogLevel - log level label
        ///   m_comboLogLevel - log level combobox
        ///   m_buttonBox - horizontal box as button container box
        ///   m_buttonOk - ok button (save changes)
        ///   m_buttonCancel - cancel button (dissmiss changes)
        SettingsSetup m_setup{};
        SigSetup m_setupSignal{};
        Gtk::Box m_boxRoot{};
        Gtk::Notebook m_notebook{};
        Gtk::Box m_boxSerial{};
        Gtk::Label m_labelSerialPath{};
        Gtk::Entry m_entrySerialPath{};
        Gtk::Label m_labelSerialBaud{};
        Gtk::ComboBoxText m_comboSerialBaud{};
        Gtk::Label m_labelSerialData{};
        Gtk::ComboBoxText m_comboSerialData{};
        Gtk::Label m_labelSerialParity{};
        Gtk::ComboBoxText m_comboSerialParity{};
        Gtk::Label m_labelSerialStop{};
        Gtk::ComboBoxText m_comboSerialStop{};
        Gtk::Label m_labelSerialFlowControl{};
        Gtk::ComboBoxText m_comboSerialFlowControl{};
        Gtk::Box m_boxLog{};
        Gtk::Label m_labelLogPath{};
        Gtk::Entry m_entryLogPath{};
        Gtk::Label m_labelLogLevel{};
        Gtk::ComboBoxText m_comboLogLevel{};
        Gtk::Grid m_buttonBox{};
        Gtk::Button m_buttonOk{};
        Gtk::Button m_buttonCancel{};
    };
};

