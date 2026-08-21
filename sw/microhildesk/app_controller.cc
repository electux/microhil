////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.cc
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <app_controller.h>
#include <config/config_manager.h>
#include <model/model.h>
#include <com/serial_com.h>
#include <com/serial_utils.h>
#include <log/log.h>
#include <format>
#include <vector>
#include <string>

using namespace Electux::App;

AppController::AppController()
	: m_configManager(std::make_unique<Config::ConfigManager>())
{
	auto serial = std::make_unique<Com::SerialCom>();
	m_serialConfig = serial.get();
	m_comChannel = std::move(serial);
	m_logger = std::make_unique<Logger::Log>();
}

AppController::~AppController() = default;

void AppController::startup()
{
	m_configManager->init();
	configureLogger();
	configureSerial();
	m_logger->log("Application started.", Logger::LogLevel::Info);
}

void AppController::shutdown()
{
	if (m_logger)
	{
		m_logger->log("Application shutting down.", Logger::LogLevel::Info);
		m_logger->close();
	}
	if (m_comChannel)
	{
		m_comChannel->close();
	}
	m_configManager->store();
}

void AppController::configureLogger()
{
	if (!m_logger) { return; }

	m_logger->close();

	auto& config = getModel();
	auto pathKey = config.toString(Model::ModelLogKey::FilePath);
	auto levelKey = config.toString(Model::ModelLogKey::LogLevel);

	m_logger->setOutputFile(config.getEntity(pathKey));
	
	uint32_t levelIdx = static_cast<uint32_t>(std::stoul(config.getEntity(levelKey)));
	m_logger->setLevel(static_cast<Logger::LogLevel>(levelIdx));

	m_logger->open();
}

void AppController::configureSerial()
{
	if (!m_comChannel || !m_serialConfig) { return; }

	m_comChannel->close();

	auto& config = getModel();
	
	Com::SerialParams params;
	params.device = config.getEntity(config.toString(Model::ModelSerialKey::Device));

	uint32_t baudIdx = static_cast<uint32_t>(std::stoul(config.getEntity(config.toString(Model::ModelSerialKey::Baud))));
	params.baud = Com::SerialUtils::uintToBaud(baudIdx);

	uint32_t dataIdx = static_cast<uint32_t>(std::stoul(config.getEntity(config.toString(Model::ModelSerialKey::Data))));
	params.data = Com::SerialUtils::uintToDataBits(dataIdx);

	uint32_t parityIdx = static_cast<uint32_t>(std::stoul(config.getEntity(config.toString(Model::ModelSerialKey::Parity))));
	params.parity = Com::SerialUtils::uintToParity(parityIdx);

	uint32_t stopIdx = static_cast<uint32_t>(std::stoul(config.getEntity(config.toString(Model::ModelSerialKey::Stop))));
	params.stop = Com::SerialUtils::uintToStopBits(stopIdx);

	uint32_t flowIdx = static_cast<uint32_t>(std::stoul(config.getEntity(config.toString(Model::ModelSerialKey::Flow))));
	params.flow = Com::SerialUtils::uintToFlowControl(flowIdx);

	m_serialConfig->setDevice(params.device);
	if (m_comChannel->open())
	{
		m_serialConfig->setup(params);
	}
}

Model::IModel& AppController::getModel()
{
	return const_cast<Model::IModel&>(m_configManager->getConfig());
}

const Model::IModel& AppController::getModel() const
{
	return m_configManager->getConfig();
}

void AppController::onSetupChanged(const Model::SettingsSetup &setup)
{
	const auto& oldConfig = m_configManager->getConfig();
	auto& newConfig = *setup.m_config;

	// Check channel updates
	for (size_t i = 0; i < Model::Channel::cNumOfChannels; ++i)
	{
		auto oldState = oldConfig.getChannelState(i);
		auto newState = newConfig.getChannelState(i);

		if (oldState.enabled != newState.enabled ||
			oldState.mode != newState.mode ||
			oldState.toggle != newState.toggle ||
			oldState.timer != newState.timer ||
			oldState.timerEnabled != newState.timerEnabled)
		{
			// 1. Log change
			std::string logMsg = std::format(
				"Channel {} state changed: enabled={}, mode={}, toggle={}, timer={}, timerEnabled={}",
				i, newState.enabled, newState.mode, newState.toggle, newState.timer, newState.timerEnabled
			);
			m_logger->log(logMsg, Logger::LogLevel::Info);

			// 2. Transmit via serial
			std::string cmd = std::format(
				"CH{}:{},{},{},{},{}\n",
				i, newState.enabled ? 1 : 0, newState.mode, newState.toggle ? 1 : 0, newState.timer, newState.timerEnabled ? 1 : 0
			);
			std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
			if (m_comChannel && m_comChannel->isOpen())
			{
				m_comChannel->write(cmdBytes);
			}
		}
	}

	// Check if serial configs changed
	bool serialChanged = false;
	for (int k = static_cast<int>(Model::ModelSerialKey::Device); k <= static_cast<int>(Model::ModelSerialKey::Flow); ++k)
	{
		auto key = oldConfig.toString(static_cast<Model::ModelSerialKey>(k));
		if (oldConfig.getEntity(key) != newConfig.getEntity(key))
		{
			serialChanged = true;
			break;
		}
	}

	// Check if log configs changed
	bool logChanged = false;
	for (int k = static_cast<int>(Model::ModelLogKey::FilePath); k <= static_cast<int>(Model::ModelLogKey::LogLevel); ++k)
	{
		auto key = oldConfig.toString(static_cast<Model::ModelLogKey>(k));
		if (oldConfig.getEntity(key) != newConfig.getEntity(key))
		{
			logChanged = true;
			break;
		}
	}

	m_configManager->setConfig(newConfig);
	m_configManager->store();

	// Reconfigure layers
	if (logChanged)
	{
		configureLogger();
	}
	if (serialChanged)
	{
		configureSerial();
	}

	getModel().emit_changed();
}
