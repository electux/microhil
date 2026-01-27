/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_slots.cc
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

using namespace Electux::App::View::Settings;

void AppSettings::updateUiData()
{
    std::string serialConfigPathKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Device);
    m_entrySerialPath.set_text(m_setup.m_serialConfig.getEntity(serialConfigPathKey).data());
    std::string serialConfigBaudKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud);
    int serialConfigBaudValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigBaudKey).data());
    m_comboSerialBaud.set_active(serialConfigBaudValue);
    std::string serialConfigDataKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Data);
    int serialConfigDataValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigDataKey).data());
    m_comboSerialData.set_active(serialConfigDataValue);
    std::string serialConfigParityKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity);
    int serialConfigParityValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigParityKey).data());
    m_comboSerialParity.set_active(serialConfigParityValue);
    std::string serialConfigStopKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop);
    int serialConfigStopValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigStopKey).data());
    m_comboSerialStop.set_active(serialConfigStopValue);
    std::string serialConfigFlowControlKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow);
    int serialConfigFlowControlValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigFlowControlKey).data());
    m_comboSerialFlowControl.set_active(serialConfigFlowControlValue);
    std::string logConfigPathKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::FilePath);
    m_entryLogPath.set_text(m_setup.m_logConfig.getEntity(logConfigPathKey).data());
    std::string logConfigLevelKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    int logConfigLevelValue = std::stoi(m_setup.m_logConfig.getEntity(logConfigLevelKey).data());
    m_comboLogLevel.set_active(logConfigLevelValue);
}

void AppSettings::getUiData()
{
    m_setup.m_serialConfig.clear();
    std::string serialConfigPathKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Device);
    std::string serialConfigPathValue = m_entrySerialPath.get_text().raw();
    m_setup.m_serialConfig.add(serialConfigPathKey, serialConfigPathValue);
    std::string serialConfigBaudKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud);
    int serialConfigBaudComboValue = m_comboSerialBaud.get_active_row_number();
    std::string serialConfigBaudValue = std::to_string(serialConfigBaudComboValue);
    m_setup.m_serialConfig.add(serialConfigBaudKey, serialConfigBaudValue);
    std::string serialConfigDataKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Data);
    int serialConfigDataComboValue = m_comboSerialData.get_active_row_number();
    std::string serialConfigDataValue = std::to_string(serialConfigDataComboValue);
    m_setup.m_serialConfig.add(serialConfigDataKey, serialConfigDataValue);
    std::string serialConfigParityKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity);
    int serialConfigParityComboValue = m_comboSerialParity.get_active_row_number();
    std::string serialConfigParityValue = std::to_string(serialConfigParityComboValue);
    m_setup.m_serialConfig.add(serialConfigParityKey, serialConfigParityValue);
    std::string serialConfigStopKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop);
    int serialConfigStopComboValue = m_comboSerialStop.get_active_row_number();
    std::string serialConfigStopValue = std::to_string(serialConfigStopComboValue);
    m_setup.m_serialConfig.add(serialConfigStopKey, serialConfigStopValue);
    std::string serialConfigFlowControlKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow);
    int serialConfigFlowControlComboValue = m_comboSerialFlowControl.get_active_row_number();
    std::string serialConfigFlowControlValue = std::to_string(serialConfigFlowControlComboValue);
    m_setup.m_serialConfig.add(serialConfigFlowControlKey, serialConfigFlowControlValue);
    m_setup.m_logConfig.clear();
    std::string logConfigPathKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::FilePath);
    std::string logConfigPathValue = m_entryLogPath.get_text().raw();
    m_setup.m_logConfig.add(logConfigPathKey, logConfigPathValue);
    std::string logConfigLevelKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    int logConfigLevelComboValue = m_comboLogLevel.get_active_row_number();
    std::string logConfigLevelValue = std::to_string(logConfigLevelComboValue);
    m_setup.m_logConfig.add(logConfigLevelKey, logConfigLevelValue);
}

void AppSettings::onButtonOkClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Performs action on OK button emit signal for changed settings
    getUiData();
    m_setupSignal.emit(m_setup);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window
    hide();
}

void AppSettings::onButtonCancelClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window
    hide();
}

SigSetup AppSettings::setupChanged() { return m_setupSignal; }
