/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings.cc
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
#include "settings.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application settings window widgets parameters
    ///   settings_title - window title
    ///   settings_width - window width
    ///   settings_height - window height
    ///   settings_notebook_margin - notebook margin
    ///   settings_serial_path - label serial path
    ///   settings_serial_baud - label baud rate
    ///   settings_serial_data - label data bits
    ///   settings_serial_parity - label parity
    ///   settings_serial_stop - label stop bits
    ///   settings_page_serial_label - notebook page label serial
    ///   settings_log_path - label log file path
    ///   settings_log_level - label log level
    ///   settings_page_log_label - notebook page label log
    ///   settings_button_box_width - button box width
    ///   settings_button_box_height - button box height
    ///   settings_button_box_margin - button box margin
    ///   settings_button_box_row_spacing - button box row spacing
    ///   settings_button_box_column_spacing -  button box column spacing
    ///   settings_button_ok_label - button ok label
    ///   settings_button_cancel_label - button cancel label
    ///   settings_button_width - button width
    ///   settings_button_height - button height
    ///   settings_grid_row_column_occupy_zero - Position widget occupy (0)
    ///   settings_grid_row_column_occupy_one - Position widget occupy (1)
    constexpr const char settings_title[]{"microhildesk"};
    constexpr int settings_width{320};
    constexpr int settings_height{280};
    constexpr int settings_notebook_margin{10};
    constexpr const char settings_serial_path[]{"Device port"};
    constexpr const char settings_serial_baud[]{"Baud rate"};
    constexpr const char settings_serial_data[]{"Data bits"};
    constexpr const char settings_serial_parity[]{"Parity"};
    constexpr const char settings_serial_stop[]{"Stop bits"};
    constexpr const char settings_page_serial_label[]{"Serial port"};
    constexpr const char settings_log_path[]{"Log file path"};
    constexpr const char settings_log_level[]{"Log level"};
    constexpr const char settings_page_log_label[]{"Log"};
    constexpr int settings_button_box_width{220};
    constexpr int settings_button_box_height{60};
    constexpr int settings_button_box_margin{10};
    constexpr int settings_button_box_row_spacing{5};
    constexpr int settings_button_box_column_spacing{5};
    constexpr const char settings_button_ok_label[]{"Ok"};
    constexpr const char settings_button_cancel_label[]{"Cancel"};
    constexpr int settings_button_width{100};
    constexpr int settings_button_height{50};
    constexpr int settings_grid_row_column_occupy_zero{0};
    constexpr int settings_grid_row_column_occupy_one{1};
};

using namespace Electux::App::View::Settings;

AppSettings::AppSettings()
{
    //////////////////////////////////////////////////////////////////////////
    /// Setup application settings window
    set_title(settings_title);
    set_default_size(settings_width, settings_height);
    set_resizable(false);
    set_hide_on_close(true);
    set_child(m_box_root);
    m_box_root.set_orientation(Gtk::Orientation::VERTICAL);
    m_notebook.set_margin(settings_notebook_margin);
    m_notebook.set_expand();

    //////////////////////////////////////////////////////////////////////////
    /// Setup serial port settings page
    m_box_serial.set_orientation(Gtk::Orientation::VERTICAL);
    m_label_serial_path.set_label(settings_serial_path);
    m_box_serial.append(m_label_serial_path);
    m_box_serial.append(m_entry_serial_path);
    m_label_serial_baud.set_label(settings_serial_baud);
    m_box_serial.append(m_label_serial_baud);
    m_box_serial.append(m_combo_serial_baud);
    m_label_serial_data.set_label(settings_serial_data);
    m_box_serial.append(m_label_serial_data);
    m_box_serial.append(m_combo_serial_data);
    m_label_serial_parity.set_label(settings_serial_parity);
    m_box_serial.append(m_label_serial_parity);
    m_box_serial.append(m_combo_serial_parity);
    m_label_serial_stop.set_label(settings_serial_stop);
    m_box_serial.append(m_label_serial_stop);
    m_box_serial.append(m_combo_serial_stop);
    m_notebook.append_page(m_box_serial, settings_page_serial_label);

    //////////////////////////////////////////////////////////////////////////
    /// Setup log settings page
    m_box_log.set_orientation(Gtk::Orientation::VERTICAL);
    m_label_log_path.set_label(settings_log_path);
    m_box_log.append(m_label_log_path);
    m_box_log.append(m_entry_log_path);
    m_label_log_level.set_label(settings_log_level);
    m_box_log.append(m_label_log_level);
    m_box_log.append(m_combo_log_level);
    m_notebook.append_page(m_box_log, settings_page_log_label);
    m_box_root.append(m_notebook);
    m_button_box.set_size_request(
        settings_button_box_width, settings_button_box_height
    );
    m_button_box.set_margin(settings_button_box_margin);
    m_button_ok.set_label(settings_button_ok_label);
    m_button_ok.set_size_request(
        settings_button_width, settings_button_height
    );
    m_button_cancel.set_label(settings_button_cancel_label);
    m_button_cancel.set_size_request(
        settings_button_width, settings_button_height
    );
    m_button_box.attach(
        m_button_cancel,
        settings_grid_row_column_occupy_zero,
        settings_grid_row_column_occupy_zero
    );
    m_button_box.attach(
        m_button_ok,
        settings_grid_row_column_occupy_one,
        settings_grid_row_column_occupy_zero
    );
    m_button_box.set_hexpand(false);
    m_button_box.set_vexpand(false);
    m_button_box.set_row_spacing(settings_button_box_row_spacing);
    m_button_box.set_column_spacing(settings_button_box_column_spacing);
    m_box_root.append(m_button_box);

    ////////////////////////////////////////////////////////////////////////
    /// Maps settings, log (signals and slots)
    mapping();
}

