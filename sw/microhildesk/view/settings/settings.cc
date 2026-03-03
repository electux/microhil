////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <view/settings/settings.h>
#include <params/serial_com_params.h>
#include <params/log_level_params.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Settings Window Widgets Parameters
	/// @{
	constexpr std::string_view cSettingsTitle{"microhildesk"};
	constexpr int cSettingsWidth{320};
	constexpr int cSettingsHeight{280};
	constexpr int cSettingsNotebookMargin{10};
	constexpr std::string_view cSettingsSerialPath{"Device port"};
	constexpr std::string_view cSettingsSerialBaud{"Baud rate"};
	constexpr std::string_view cSettingsSerialData{"Data bits"};
	constexpr std::string_view cSettingsSerialParity{"Parity"};
	constexpr std::string_view cSettingsSerialStop{"Stop bits"};
	constexpr std::string_view cSettingsSerialFlowControl{"Flow control"};
	constexpr std::string_view cSettingsPageSerialLabel{"Serial port"};
	constexpr std::string_view cSettingsLogPath{"Log file path"};
	constexpr std::string_view cSettingsLogLevel{"Log level"};
	constexpr std::string_view cSettingsPageLogLabel{"Log"};
	constexpr int cSettingsButtonBoxWidth{220};
	constexpr int cSettingsButtonBoxHeight{60};
	constexpr int cSettingsButtonBoxMargin{10};
	constexpr int cSettingsButtonBoxRowSpacing{5};
	constexpr int cSettingsButtonBoxColumnSpacing{5};
	constexpr std::string_view cSettingsButtonOkLabel{"Ok"};
	constexpr std::string_view cSettingsButtonCancelLabel{"Cancel"};
	constexpr int cSettingsButtonWidth{100};
	constexpr int cSettingsButtonHeight{50};
	constexpr int cSettingsGridRowColumnOccupyZero{0};
	constexpr int cSettingsGridRowColumnOccupyOne{1};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Params::SerialComConstants;
using namespace Electux::App::Params::LogLevels;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief AppSettings constructor.
///
/// Initializes the settings window, sets up the notebook with Serial and Log
/// pages, and populates all ComboBox widgets from global parameters.
////////////////////////////////////////////////////////////////////////////////////////////////////////
AppSettings::AppSettings()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Setup application settings window
	set_title(cSettingsTitle.data());
	set_default_size(cSettingsWidth, cSettingsHeight);
	set_resizable(false);
	set_hide_on_close(true);
	set_child(m_boxRoot);
	m_boxRoot.set_orientation(Gtk::Orientation::VERTICAL);
	m_notebook.set_margin(cSettingsNotebookMargin);
	m_notebook.set_expand();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Setup serial port settings page
	m_boxSerial.set_orientation(Gtk::Orientation::VERTICAL);
	
	m_labelSerialPath.set_label(cSettingsSerialPath.data());
	m_boxSerial.append(m_labelSerialPath);
	m_boxSerial.append(m_entrySerialPath);

	m_labelSerialBaud.set_label(cSettingsSerialBaud.data());
	m_boxSerial.append(m_labelSerialBaud);
	for (const auto& rate : cComBaudRates)
	{
		m_comboSerialBaud.append(std::string(rate));
	}
	m_boxSerial.append(m_comboSerialBaud);

	m_labelSerialData.set_label(cSettingsSerialData.data());
	m_boxSerial.append(m_labelSerialData);
	for (const auto& data : cComDataBits)
	{
		m_comboSerialData.append(std::string(data));
	}
	m_boxSerial.append(m_comboSerialData);

	m_labelSerialParity.set_label(cSettingsSerialParity.data());
	m_boxSerial.append(m_labelSerialParity);
	for (const auto& parity : cComParities)
	{
		m_comboSerialParity.append(std::string(parity));
	}
	m_boxSerial.append(m_comboSerialParity);

	m_labelSerialStop.set_label(cSettingsSerialStop.data());
	m_boxSerial.append(m_labelSerialStop);
	for (const auto& stop : cComStopBits)
	{
		m_comboSerialStop.append(std::string(stop));
	}
	m_boxSerial.append(m_comboSerialStop);

	m_labelSerialFlowControl.set_label(cSettingsSerialFlowControl.data());
	m_boxSerial.append(m_labelSerialFlowControl);
	for (const auto& flow : cComFlowControls)
	{
		m_comboSerialFlowControl.append(std::string(flow));
	}
	m_boxSerial.append(m_comboSerialFlowControl);

	m_notebook.append_page(m_boxSerial, cSettingsPageSerialLabel.data());

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Setup log settings page
	m_boxLog.set_orientation(Gtk::Orientation::VERTICAL);
	
	m_labelLogPath.set_label(cSettingsLogPath.data());
	m_boxLog.append(m_labelLogPath);
	m_boxLog.append(m_entryLogPath);

	m_labelLogLevel.set_label(cSettingsLogLevel.data());
	m_boxLog.append(m_labelLogLevel);
	for (const auto& level : cLogLevels)
	{
		m_comboLogLevel.append(std::string(level));
	}
	m_boxLog.append(m_comboLogLevel);

	m_notebook.append_page(m_boxLog, cSettingsPageLogLabel.data());
	m_boxRoot.append(m_notebook);

	// Setup Button Box (Ok/Cancel)
	m_buttonBox.set_size_request(cSettingsButtonBoxWidth, cSettingsButtonBoxHeight);
	m_buttonBox.set_margin(cSettingsButtonBoxMargin);
	
	m_buttonOk.set_label(cSettingsButtonOkLabel.data());
	m_buttonOk.set_size_request(cSettingsButtonWidth, cSettingsButtonHeight);
	
	m_buttonCancel.set_label(cSettingsButtonCancelLabel.data());
	m_buttonCancel.set_size_request(cSettingsButtonWidth, cSettingsButtonHeight);
	
	m_buttonBox.attach(m_buttonCancel, cSettingsGridRowColumnOccupyZero, cSettingsGridRowColumnOccupyZero);
	m_buttonBox.attach(m_buttonOk, cSettingsGridRowColumnOccupyOne, cSettingsGridRowColumnOccupyZero);
	
	m_buttonBox.set_hexpand(false);
	m_buttonBox.set_vexpand(false);
	m_buttonBox.set_row_spacing(cSettingsButtonBoxRowSpacing);
	m_buttonBox.set_column_spacing(cSettingsButtonBoxColumnSpacing);
	
	m_boxRoot.append(m_buttonBox);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Maps signals and slots
	mapping();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the internal configuration setup.
/// @param setup Constant reference to the SettingsSetup object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::setSettingsSetup(const SettingsSetup& setup)
{
	m_setup = setup;
}
