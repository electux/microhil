////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_manager_utils.cc
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

#include <config/config_manager.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Configuration Constants
	/// @{
	// Default values for Control Model
	constexpr std::string_view cConfigDefaultControlEnable{"false false false false false false false false"};
	constexpr std::string_view cConfigDefaultControlMode{"-1 -1 -1 -1 -1 -1 -1 -1"};
	constexpr std::string_view cConfigDefaultControlToggle{"false false false false false false false false"};
	constexpr std::string_view cConfigDefaultControlTimer{"0 0 0 0 0 0 0 0"};
	constexpr std::string_view cConfigDefaultControlTimerEnable{"false false false false false false false false"};
	// Default values for Serial Model
	constexpr std::string_view cConfigDefaultSerialDevice{"/dev/ttyUSB0"};
	constexpr std::string_view cConfigDefaultSerialBaud{"10"};
	constexpr std::string_view cConfigDefaultSerialData{"3"};
	constexpr std::string_view cConfigDefaultSerialParity{"2"};
	constexpr std::string_view cConfigDefaultSerialStop{"0"};
	constexpr std::string_view cConfigDefaultSerialFlow{"0"};
	// Default values for Log Model
	constexpr std::string_view cConfigDefaultLogFilePath{"/tmp/microhildesk.log"};
	constexpr std::string_view cConfigDefaultLogLevel{"2"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::Config;
using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Populates models with hardcoded defaults and persists them.
///
/// This method is typically called when no configuration file is found
/// or when a factory reset of the configuration is required.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::defaultConfigStore()
{
	// Set default control configuration
	const auto enableKey = m_config.toString(ModelControlKey::Enable);
	m_config.add(enableKey, cConfigDefaultControlEnable.data());
	const auto modeKey = m_config.toString(ModelControlKey::Mode);
	m_config.add(modeKey, cConfigDefaultControlMode.data());
	const auto toggleKey = m_config.toString(ModelControlKey::Toggle);
	m_config.add(toggleKey, cConfigDefaultControlToggle.data());
	const auto timerKey = m_config.toString(ModelControlKey::Timer);
	m_config.add(timerKey, cConfigDefaultControlTimer.data());
	const auto timerEnableKey = m_config.toString(ModelControlKey::TimerEnable);
	m_config.add(timerEnableKey, cConfigDefaultControlTimerEnable.data());

	// Set default serial configuration
	const auto deviceKey = m_config.toString(ModelSerialKey::Device);
	m_config.add(deviceKey, cConfigDefaultSerialDevice.data());
	const auto baudKey = m_config.toString(ModelSerialKey::Baud);
	m_config.add(baudKey, cConfigDefaultSerialBaud.data());
	const auto dataKey = m_config.toString(ModelSerialKey::Data);
	m_config.add(dataKey, cConfigDefaultSerialData.data());
	const auto parityKey = m_config.toString(ModelSerialKey::Parity);
	m_config.add(parityKey, cConfigDefaultSerialParity.data());
	const auto stopKey = m_config.toString(ModelSerialKey::Stop);
	m_config.add(stopKey, cConfigDefaultSerialStop.data());
	const auto flowKey = m_config.toString(ModelSerialKey::Flow);
	m_config.add(flowKey, cConfigDefaultSerialFlow.data());

	// Set default log configuration
	const auto filePathKey = m_config.toString(ModelLogKey::FilePath);
	m_config.add(filePathKey, cConfigDefaultLogFilePath.data());
	const auto logLevelKey = m_config.toString(ModelLogKey::LogLevel);
	m_config.add(logLevelKey, cConfigDefaultLogLevel.data());

	// Finalize by storing to disk
	store();
}
