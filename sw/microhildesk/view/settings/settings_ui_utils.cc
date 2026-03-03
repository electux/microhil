////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings_ui_utils.cc
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

using namespace Electux::App::Model;
using namespace Electux::App::View::Settings;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Updates UI widgets with data from loaded configuration.
/// 
/// Synchronizes serial port and logging widgets with current model values.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::updateUiData()
{
	// Updates UI widgets with data from loaded configuration for serial
	auto serialConfigPathKey = m_setup.m_config.toString(ModelSerialKey::Device);
	m_entrySerialPath.set_text(m_setup.m_config.getEntity(serialConfigPathKey).data());

	auto serialConfigBaudKey = m_setup.m_config.toString(ModelSerialKey::Baud);
	auto serialConfigBaudValue = std::stoi(m_setup.m_config.getEntity(serialConfigBaudKey).data());
	m_comboSerialBaud.set_active(serialConfigBaudValue);

	auto serialConfigDataKey = m_setup.m_config.toString(ModelSerialKey::Data);
	auto serialConfigDataValue = std::stoi(m_setup.m_config.getEntity(serialConfigDataKey).data());
	m_comboSerialData.set_active(serialConfigDataValue);

	auto serialConfigParityKey = m_setup.m_config.toString(ModelSerialKey::Parity);
	auto serialConfigParityValue = std::stoi(m_setup.m_config.getEntity(serialConfigParityKey).data());
	m_comboSerialParity.set_active(serialConfigParityValue);

	auto serialConfigStopKey = m_setup.m_config.toString(ModelSerialKey::Stop);
	auto serialConfigStopValue = std::stoi(m_setup.m_config.getEntity(serialConfigStopKey).data());
	m_comboSerialStop.set_active(serialConfigStopValue);

	auto serialConfigFlowControlKey = m_setup.m_config.toString(ModelSerialKey::Flow);
	auto serialConfigFlowControlValue = std::stoi(m_setup.m_config.getEntity(serialConfigFlowControlKey).data());
	m_comboSerialFlowControl.set_active(serialConfigFlowControlValue);
    
	// Updates UI widgets with data from loaded configuration for log
	auto logConfigPathKey = m_setup.m_config.toString(ModelLogKey::FilePath);
	m_entryLogPath.set_text(m_setup.m_config.getEntity(logConfigPathKey).data());

	auto logConfigLevelKey = m_setup.m_config.toString(ModelLogKey::LogLevel);
	auto logConfigLevelValue = std::stoi(m_setup.m_config.getEntity(logConfigLevelKey).data());
	m_comboLogLevel.set_active(logConfigLevelValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets UI data from widgets and saves them to configuration models.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::getUiData()
{
	// Gets UI data from widgets and saves them to configuration for serial
	auto serialConfigPathKey = m_setup.m_config.toString(ModelSerialKey::Device);
	auto serialConfigPathValue = m_entrySerialPath.get_text().raw();
	m_setup.m_config.update(serialConfigPathKey, serialConfigPathValue);

	auto serialConfigBaudKey = m_setup.m_config.toString(ModelSerialKey::Baud);
	int serialConfigBaudComboValue = m_comboSerialBaud.get_active_row_number();
	auto serialConfigBaudValue = std::to_string(serialConfigBaudComboValue);
	m_setup.m_config.update(serialConfigBaudKey, serialConfigBaudValue);

	auto serialConfigDataKey = m_setup.m_config.toString(ModelSerialKey::Data);
	int serialConfigDataComboValue = m_comboSerialData.get_active_row_number();
	auto serialConfigDataValue = std::to_string(serialConfigDataComboValue);
	m_setup.m_config.update(serialConfigDataKey, serialConfigDataValue);

	auto serialConfigParityKey = m_setup.m_config.toString(ModelSerialKey::Parity);
	int serialConfigParityComboValue = m_comboSerialParity.get_active_row_number();
	auto serialConfigParityValue = std::to_string(serialConfigParityComboValue);
	m_setup.m_config.update(serialConfigParityKey, serialConfigParityValue);

	auto serialConfigStopKey = m_setup.m_config.toString(ModelSerialKey::Stop);
	int serialConfigStopComboValue = m_comboSerialStop.get_active_row_number();
	auto serialConfigStopValue = std::to_string(serialConfigStopComboValue);
	m_setup.m_config.update(serialConfigStopKey, serialConfigStopValue);

	auto serialConfigFlowControlKey = m_setup.m_config.toString(ModelSerialKey::Flow);
	int serialConfigFlowControlComboValue = m_comboSerialFlowControl.get_active_row_number();
	auto serialConfigFlowControlValue = std::to_string(serialConfigFlowControlComboValue);
	m_setup.m_config.update(serialConfigFlowControlKey, serialConfigFlowControlValue);
    
	// Gets UI data from widgets and saves them to configuration for log
	auto logConfigPathKey = m_setup.m_config.toString(ModelLogKey::FilePath);
	auto logConfigPathValue = m_entryLogPath.get_text().raw();
	m_setup.m_config.update(logConfigPathKey, logConfigPathValue);

	auto logConfigLevelKey = m_setup.m_config.toString(ModelLogKey::LogLevel);
	int logConfigLevelComboValue = m_comboLogLevel.get_active_row_number();
	auto logConfigLevelValue = std::to_string(logConfigLevelComboValue);
	m_setup.m_config.update(logConfigLevelKey, logConfigLevelValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Returns the signal for setup changes.
/// @return SigSetup instance.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SigSetup AppSettings::setupChanged() 
{ 
	return m_setupSignal; 
}
