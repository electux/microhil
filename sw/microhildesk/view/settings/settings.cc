/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings.cc
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
#include <iostream>
#include "settings.h"
#include "../../params/serial_com_params.h"
#include "../../params/log_level_params.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application settings window widgets parameters
    ///   settingsTitle - window title
    ///   settingsWidth - window width
    ///   settingsHeight - window height
    ///   settingsNotebookMargin - notebook margin
    ///   settingsSerialPath - label serial path
    ///   settingsSerialBaud - label baud rate
    ///   settingsSerialData - label data bits
    ///   settingsSerialParity - label parity
    ///   settingsSerialStop - label stop bits
    ///   settingsSerialFlowControl - label flow control
    ///   settingsPageSerialLabel - notebook page label serial
    ///   settingsLogPath - label log file path
    ///   settingsLogLevel - label log level
    ///   settingsPageLogLabel - notebook page label log
    ///   settingsButtonBoxWidth - button box width
    ///   settingsButtonBoxHeight - button box height
    ///   settingsButtonBoxMargin - button box margin
    ///   settingsButtonBoxRowSpacing - button box row spacing
    ///   settingsButtonBoxColumnSpacing -  button box column spacing
    ///   settingsButtonOkLabel - button ok label
    ///   settingsButtonCancelLabel - button cancel label
    ///   settingsButtonWidth - button width
    ///   settingsButtonHeight - button height
    ///   settingsGridRowColumnOccupyZero - position widget occupy (0)
    ///   settingsGridRowColumnOccupyOne - position widget occupy (1)
    constexpr std::string_view settingsTitle{"microhildesk"};
    constexpr int settingsWidth{320};
    constexpr int settingsHeight{280};
    constexpr int settingsNotebookMargin{10};
    constexpr std::string_view settingsSerialPath{"Device port"};
    constexpr std::string_view settingsSerialBaud{"Baud rate"};
    constexpr std::string_view settingsSerialData{"Data bits"};
    constexpr std::string_view settingsSerialParity{"Parity"};
    constexpr std::string_view settingsSerialStop{"Stop bits"};
    constexpr std::string_view settingsSerialFlowControl{"Flow control"};
    constexpr std::string_view settingsPageSerialLabel{"Serial port"};
    constexpr std::string_view settingsLogPath{"Log file path"};
    constexpr std::string_view settingsLogLevel{"Log level"};
    constexpr std::string_view settingsPageLogLabel{"Log"};
    constexpr int settingsButtonBoxWidth{220};
    constexpr int settingsButtonBoxHeight{60};
    constexpr int settingsButtonBoxMargin{10};
    constexpr int settingsButtonBoxRowSpacing{5};
    constexpr int settingsButtonBoxColumnSpacing{5};
    constexpr std::string_view settingsButtonOkLabel{"Ok"};
    constexpr std::string_view settingsButtonCancelLabel{"Cancel"};
    constexpr int settingsButtonWidth{100};
    constexpr int settingsButtonHeight{50};
    constexpr int settingsGridRowColumnOccupyZero{0};
    constexpr int settingsGridRowColumnOccupyOne{1};
};

using namespace Electux::App::View::Settings;
using namespace Electux::App::Params::SerialComConstants;
using namespace Electux::App::Params::LogLevels;

AppSettings::AppSettings()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup application settings window
    set_title(settingsTitle.data());
    set_default_size(settingsWidth, settingsHeight);
    set_resizable(false);
    set_hide_on_close(true);
    set_child(m_boxRoot);
    m_boxRoot.set_orientation(Gtk::Orientation::VERTICAL);
    m_notebook.set_margin(settingsNotebookMargin);
    m_notebook.set_expand();

    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup serial port settings page
    m_boxSerial.set_orientation(Gtk::Orientation::VERTICAL);
    m_labelSerialPath.set_label(settingsSerialPath.data());
    m_boxSerial.append(m_labelSerialPath);
    m_boxSerial.append(m_entrySerialPath);
    m_labelSerialBaud.set_label(settingsSerialBaud.data());
    m_boxSerial.append(m_labelSerialBaud);
    for (const auto& rate : comBaudRates)
    {
        m_comboSerialBaud.append(std::string(rate));
    }
    m_boxSerial.append(m_comboSerialBaud);
    m_labelSerialData.set_label(settingsSerialData.data());
    m_boxSerial.append(m_labelSerialData);
    for (const auto& data : comDataBits)
    {
        m_comboSerialData.append(std::string(data));
    }
    m_boxSerial.append(m_comboSerialData);
    m_labelSerialParity.set_label(settingsSerialParity.data());
    m_boxSerial.append(m_labelSerialParity);
    for (const auto& parity : comParities)
    {
        m_comboSerialParity.append(std::string(parity));
    }
    m_boxSerial.append(m_comboSerialParity);
    m_labelSerialStop.set_label(settingsSerialStop.data());
    m_boxSerial.append(m_labelSerialStop);
    for (const auto& stop : comStopBits)
    {
        m_comboSerialStop.append(std::string(stop));
    }
    m_boxSerial.append(m_comboSerialStop);
    m_labelSerialFlowControl.set_label(settingsSerialFlowControl.data());
    m_boxSerial.append(m_labelSerialFlowControl);
    for (const auto& flow : comFlowControls)
    {
        m_comboSerialFlowControl.append(std::string(flow));
    }
    m_boxSerial.append(m_comboSerialFlowControl);
    m_notebook.append_page(m_boxSerial, settingsPageSerialLabel.data());

    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup log settings page
    m_boxLog.set_orientation(Gtk::Orientation::VERTICAL);
    m_labelLogPath.set_label(settingsLogPath.data());
    m_boxLog.append(m_labelLogPath);
    m_boxLog.append(m_entryLogPath);
    m_labelLogLevel.set_label(settingsLogLevel.data());
    m_boxLog.append(m_labelLogLevel);
    for (const auto& level : logLevels)
    {
        m_comboLogLevel.append(std::string(level));
    }
    m_boxLog.append(m_comboLogLevel);
    m_notebook.append_page(m_boxLog, settingsPageLogLabel.data());
    m_boxRoot.append(m_notebook);
    m_buttonBox.set_size_request(settingsButtonBoxWidth, settingsButtonBoxHeight);
    m_buttonBox.set_margin(settingsButtonBoxMargin);
    m_buttonOk.set_label(settingsButtonOkLabel.data());
    m_buttonOk.set_size_request(settingsButtonWidth, settingsButtonHeight);
    m_buttonCancel.set_label(settingsButtonCancelLabel.data());
    m_buttonCancel.set_size_request(settingsButtonWidth, settingsButtonHeight);
    m_buttonBox.attach(m_buttonCancel, settingsGridRowColumnOccupyZero, settingsGridRowColumnOccupyZero);
    m_buttonBox.attach(m_buttonOk, settingsGridRowColumnOccupyOne, settingsGridRowColumnOccupyZero);
    m_buttonBox.set_hexpand(false);
    m_buttonBox.set_vexpand(false);
    m_buttonBox.set_row_spacing(settingsButtonBoxRowSpacing);
    m_buttonBox.set_column_spacing(settingsButtonBoxColumnSpacing);
    m_boxRoot.append(m_buttonBox);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps channels (signals and slots)
    mapping();
}

void AppSettings::setSettingsSetup(const SettingsSetup& setup)
{
    m_setup = setup;
}
