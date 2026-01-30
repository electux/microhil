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
#include "settings.h"

using namespace Electux::App::View::Settings;

void AppSettings::updateUiData()
{
    /////////////////////////////////////////////////////////////////////////////////
    /// @brief Updates UI widgets with data from loaded configuration for serial
    auto serialConfigPathKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Device);
    m_entrySerialPath.set_text(m_setup.m_serialConfig.getEntity(serialConfigPathKey).data());
    auto serialConfigBaudKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud);
    auto serialConfigBaudValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigBaudKey).data());
    m_comboSerialBaud.set_active(serialConfigBaudValue);
    auto serialConfigDataKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Data);
    auto serialConfigDataValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigDataKey).data());
    m_comboSerialData.set_active(serialConfigDataValue);
    auto serialConfigParityKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity);
    auto serialConfigParityValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigParityKey).data());
    m_comboSerialParity.set_active(serialConfigParityValue);
    auto serialConfigStopKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop);
    auto serialConfigStopValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigStopKey).data());
    m_comboSerialStop.set_active(serialConfigStopValue);
    auto serialConfigFlowControlKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow);
    auto serialConfigFlowControlValue = std::stoi(m_setup.m_serialConfig.getEntity(serialConfigFlowControlKey).data());
    m_comboSerialFlowControl.set_active(serialConfigFlowControlValue);
    
    /////////////////////////////////////////////////////////////////////////////////
    /// @brief Updates UI widgets with data from loaded configuration for log
    auto logConfigPathKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::FilePath);
    m_entryLogPath.set_text(m_setup.m_logConfig.getEntity(logConfigPathKey).data());
    auto logConfigLevelKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    auto logConfigLevelValue = std::stoi(m_setup.m_logConfig.getEntity(logConfigLevelKey).data());
    m_comboLogLevel.set_active(logConfigLevelValue);
}

void AppSettings::getUiData()
{
    /////////////////////////////////////////////////////////////////////////////////
    /// @brief Gets UI data from widgets and saves them to configuration for serial
    auto serialConfigPathKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Device);
    auto serialConfigPathValue = m_entrySerialPath.get_text().raw();
    m_setup.m_serialConfig.update(serialConfigPathKey, serialConfigPathValue);
    auto serialConfigBaudKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud);
    int serialConfigBaudComboValue = m_comboSerialBaud.get_active_row_number();
    auto serialConfigBaudValue = std::to_string(serialConfigBaudComboValue);
    m_setup.m_serialConfig.update(serialConfigBaudKey, serialConfigBaudValue);
    auto serialConfigDataKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Data);
    int serialConfigDataComboValue = m_comboSerialData.get_active_row_number();
    auto serialConfigDataValue = std::to_string(serialConfigDataComboValue);
    m_setup.m_serialConfig.update(serialConfigDataKey, serialConfigDataValue);
    auto serialConfigParityKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity);
    int serialConfigParityComboValue = m_comboSerialParity.get_active_row_number();
    auto serialConfigParityValue = std::to_string(serialConfigParityComboValue);
    m_setup.m_serialConfig.update(serialConfigParityKey, serialConfigParityValue);
    auto serialConfigStopKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop);
    int serialConfigStopComboValue = m_comboSerialStop.get_active_row_number();
    auto serialConfigStopValue = std::to_string(serialConfigStopComboValue);
    m_setup.m_serialConfig.update(serialConfigStopKey, serialConfigStopValue);
    auto serialConfigFlowControlKey = m_setup.m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow);
    int serialConfigFlowControlComboValue = m_comboSerialFlowControl.get_active_row_number();
    auto serialConfigFlowControlValue = std::to_string(serialConfigFlowControlComboValue);
    m_setup.m_serialConfig.update(serialConfigFlowControlKey, serialConfigFlowControlValue);
    
    /////////////////////////////////////////////////////////////////////////////////
    /// @brief Gets UI data from widgets and saves them to configuration for log
    auto logConfigPathKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::FilePath);
    auto logConfigPathValue = m_entryLogPath.get_text().raw();
    m_setup.m_logConfig.update(logConfigPathKey, logConfigPathValue);
    auto logConfigLevelKey = m_setup.m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    int logConfigLevelComboValue = m_comboLogLevel.get_active_row_number();
    auto logConfigLevelValue = std::to_string(logConfigLevelComboValue);
    m_setup.m_logConfig.update(logConfigLevelKey, logConfigLevelValue);
}

void AppSettings::onButtonOkClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Performs action on OK button emit signal for changed settings
    getUiData();
    m_setupSignal.emit(m_setup);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window after saving changes
    hide();
}

void AppSettings::onButtonCancelClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window without saving changes
    hide();
}

SigSetup AppSettings::setupChanged() { return m_setupSignal; }
