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

using namespace Electux::App::View::Settings;

AppSettings::AppSettings()
{
    set_title("microhildesk");
    set_default_size(320, 280);
    set_resizable(false);
    set_hide_on_close(true);
    set_child(m_box_root);
    m_box_root.set_orientation(Gtk::Orientation::VERTICAL);
    m_notebook.set_margin(10);
    m_notebook.set_expand();

    //////////////////////////////////////////////////////////////////////////
    /// Setup serial port settings
    m_box_serial.set_orientation(Gtk::Orientation::VERTICAL);
    m_label_serial_path.set_label("Device port");
    m_box_serial.append(m_label_serial_path);
    m_box_serial.append(m_entry_serial_path);
    m_label_serial_baud.set_label("Baud rate");
    m_box_serial.append(m_label_serial_baud);
    m_box_serial.append(m_combo_serial_baud);
    m_label_serial_data.set_label("Data bits");
    m_box_serial.append(m_label_serial_data);
    m_box_serial.append(m_combo_serial_data);
    m_label_serial_parity.set_label("Parity");
    m_box_serial.append(m_label_serial_parity);
    m_box_serial.append(m_combo_serial_parity);
    m_label_serial_stop.set_label("Stop bits");
    m_box_serial.append(m_label_serial_stop);
    m_box_serial.append(m_combo_serial_stop);
    m_notebook.append_page(m_box_serial, "Serial port");

    //////////////////////////////////////////////////////////////////////////
    /// Setup log settings
    m_box_log.set_orientation(Gtk::Orientation::VERTICAL);
    m_label_log_path.set_label("Log file path");
    m_box_log.append(m_label_log_path);
    m_box_log.append(m_entry_log_path);
    m_label_log_level.set_label("Log level");
    m_box_log.append(m_label_log_level);
    m_box_log.append(m_combo_log_level);
    m_notebook.append_page(m_box_log, "Log");
    m_box_root.append(m_notebook);
    m_button_box.set_size_request(220, 60);
    m_button_box.set_margin(10);
    m_button_ok.set_label("Ok");
    m_button_ok.set_size_request(100, 50);
    m_button_cancel.set_label("Cancel");
    m_button_cancel.set_size_request(100, 50);
    m_button_box.attach(m_button_cancel, 0, 0, 1, 1);
    m_button_box.attach(m_button_ok, 1, 0, 1, 1);
    m_button_box.set_hexpand(false);
    m_button_box.set_vexpand(false);
    m_button_box.set_row_spacing(5);
    m_button_box.set_column_spacing(5);
    m_box_root.append(m_button_box);

    //////////////////////////////////////////////////////////////////////////
    /// Connect the signal handlers to the buttons
    m_button_ok.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::on_button_ok_clicked)
    );
    m_button_cancel.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::on_button_cancel_clicked)
    );
}

void AppSettings::on_button_ok_clicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Perform action on OK button
    auto device_path = m_entry_serial_path.get_text();
    SerialParams serialParams{};
    serialParams.push_back(m_combo_serial_baud.get_active_row_number());
    serialParams.push_back(m_combo_serial_data.get_active_row_number());
    serialParams.push_back(m_combo_serial_parity.get_active_row_number());
    serialParams.push_back(m_combo_serial_stop.get_active_row_number());
    hide();
}

void AppSettings::on_button_cancel_clicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Perform action on Cancel button
    hide();
}

