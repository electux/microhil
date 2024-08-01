/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings.h
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "settings_setup.h"

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
        SigSetup setup_changed();

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Maps channels (signals and slots)
        void mapping();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action OK button
        void on_button_ok_clicked();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action Cancel button
        void on_button_cancel_clicked();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal for the serial settings
        SigSetup m_setup{};

        //////////////////////////////////////////////////////////////////////
        /// @brief Vertical box as root container
        Gtk::Box m_box_root;

        //////////////////////////////////////////////////////////////////////
        /// @brief Notebook container for settings pages serial port and log
        Gtk::Notebook m_notebook;

        //////////////////////////////////////////////////////////////////////
        /// @brief Vertical box as container box for serial settings
        ///   m_box_serial - container box for widgets
        ///   m_label_serial_path - serial path label
        ///   m_entry_serial_path - entry for serial device path
        ///   m_label_serial_baud - serial baud rate label
        ///   m_combo_serial_baud - serial baud rate combobox
        ///   m_label_serial_data - serial data bits label
        ///   m_combo_serial_data - serial data bits combobox
        ///   m_label_serial_parity - serial parity label
        ///   m_combo_serial_parity - serial parity combobox
        ///   m_label_serial_stop - serial stop bits label
        ///   m_combo_serial_stop - serial stop bits combobox
        Gtk::Box m_box_serial;
        Gtk::Label m_label_serial_path;
        Gtk::Entry m_entry_serial_path;
        Gtk::Label m_label_serial_baud;
        Gtk::ComboBoxText m_combo_serial_baud;
        Gtk::Label m_label_serial_data;
        Gtk::ComboBoxText m_combo_serial_data;
        Gtk::Label m_label_serial_parity;
        Gtk::ComboBoxText m_combo_serial_parity;
        Gtk::Label m_label_serial_stop;
        Gtk::ComboBoxText m_combo_serial_stop;

        //////////////////////////////////////////////////////////////////////
        /// @brief Vertical box as container box for log settings
        ///   m_box_log - container box for widgets
        ///   m_label_log_path - log path label 
        ///   m_entry_log_path - log file path entry
        ///   m_label_log_level - log level label
        ///   m_combo_log_level - log level combobox
        Gtk::Box m_box_log;
        Gtk::Label m_label_log_path;
        Gtk::Entry m_entry_log_path;
        Gtk::Label m_label_log_level;
        Gtk::ComboBoxText m_combo_log_level;

        //////////////////////////////////////////////////////////////////////
        /// @brief Horizontal box as button container box
        ///   m_button_box - container box for buttons
        ///   m_button_ok - ok button (save changes)
        ///   m_button_cancel - cancel button (dissmiss changes)
        Gtk::Grid m_button_box;
        Gtk::Button m_button_ok;
        Gtk::Button m_button_cancel;
    };
};

