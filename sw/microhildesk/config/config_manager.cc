/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * config_manager.cc
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
#include <glibmm/miscutils.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <sys/stat.h>
#include <filesystem>
#include <config/config_manager.h>

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration parameters
    ///   cConfigFile - program configuration file name
    ///   cConfigAssignDelimiter - delimiter for key-value assignment
    ///   cConfigCommentChar - character for comment line
    ///   cConfigDefaultControlEnable - default control configuration for enable
    ///   cConfigDefaultControlMode - default control configuration for mode
    ///   cConfigDefaultControlToggle - default control configuration for toggle
    ///   cConfigDefaultControlTimer - default control configuration for timer
    ///   cConfigDefaultControlTimerEnable - default control configuration for timer enable
    ///   cConfigDefaultSerialDevice - default serial configuration for device
    ///   cConfigDefaultSerialBaud - default serial configuration for baud rate
    ///   cConfigDefaultSerialData - default serial configuration for data bits
    ///   cConfigDefaultSerialParity - default serial configuration for parity
    ///   cConfigDefaultSerialStop - default serial configuration for stop bits
    ///   cConfigDefaultSerialFlow - default serial configuration for flow control
    ///   cConfigDefaultLogFilePath - default log configuration for log file path
    ///   cConfigDefaultLogLevel - default log configuration for log level
    constexpr std::string_view cConfigFile{".microhil/config"};
    constexpr char cConfigAssignDelimiter{'='};
    constexpr char cConfigCommentChar{'#'};
    constexpr std::string_view cConfigDefaultControlEnable{"false false false false false false false false"};
    constexpr std::string_view cConfigDefaultControlMode{"0 0 0 0 0 0 0 0"};
    constexpr std::string_view cConfigDefaultControlToggle{"false false false false false false false false"};
    constexpr std::string_view cConfigDefaultControlTimer{"0 0 0 0 0 0 0 0"};
    constexpr std::string_view cConfigDefaultControlTimerEnable{"false false false false false false false false"};
    constexpr std::string_view cConfigDefaultSerialDevice{"/dev/ttyUSB0"};
    constexpr std::string_view cConfigDefaultSerialBaud{"10"};
    constexpr std::string_view cConfigDefaultSerialData{"3"};
    constexpr std::string_view cConfigDefaultSerialParity{"2"};
    constexpr std::string_view cConfigDefaultSerialStop{"0"};
    constexpr std::string_view cConfigDefaultSerialFlow{"0"};
    constexpr std::string_view cConfigDefaultLogFilePath{"/tmp/microhildesk.log"};
    constexpr std::string_view cConfigDefaultLogLevel{"2"};
};

using namespace Electux::App::Config;
using namespace Electux::App::Model;

ConfigManager::ConfigManager()
{
    m_fileName = Glib::build_filename(Glib::get_home_dir(), cConfigFile.data());
    auto dirPath = Glib::path_get_dirname(m_fileName);

    try
    {
        if (!std::filesystem::exists(dirPath))
        {
            std::filesystem::create_directories(dirPath);
        }

        if (!std::filesystem::exists(m_fileName))
        {
            std::ofstream file(m_fileName);
            if (!file)
            {
                throw std::ios_base::failure("Unable to create file: " + m_fileName);
            }
            defaultConfigStore();
        }

        std::cout << "Setup configuration file path: " << m_fileName << std::endl;
        load();
    } catch (const std::exception& e)
    {
        std::cerr << "Error during ConfigManager initialization: " << e.what() << std::endl;
    }
}

void ConfigManager::setControlConfig(const ModelControl& config)
{
    m_controlConfig = config;
}

void ConfigManager::setSerialConfig(const ModelSerial& config)
{
    m_serialConfig = config;
}

void ConfigManager::setLogConfig(const ModelLog& config)
{
    m_logConfig = config;
}

const ModelControl& ConfigManager::getControlConfig() const
{
    return m_controlConfig;
}

const ModelSerial& ConfigManager::getSerialConfig() const
{
    return m_serialConfig; 
}

const ModelLog& ConfigManager::getLogConfig() const
{
    return m_logConfig;
}

bool ConfigManager::load()
{
    std::ifstream file(m_fileName);
    std::cout << "Loading configuration..." << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_fileName << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == cConfigCommentChar)
        {
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, cConfigAssignDelimiter) && std::getline(iss, value))
        {
            key.erase(0, key.find_first_not_of(" \t\n\r"));
            key.erase(key.find_last_not_of(" \t\n\r") + 1);
            value.erase(0, value.find_first_not_of(" \t\n\r"));
            value.erase(value.find_last_not_of(" \t\n\r") + 1);

            if (m_serialConfig.validateKey(key))
            {
                m_serialConfig.add(key, value);
            }
            else if (m_logConfig.validateKey(key))
            {
                m_logConfig.add(key, value);
            }
            else if (m_controlConfig.validateKey(key))
            {
                m_controlConfig.add(key, value);
            }
            else
            {
                std::cerr << "Warning: Unknown configuration key: " << key << std::endl;
                return false;
            }
        }
    }

    file.close();
    std::cout << "Load configuration done." << std::endl;
    return true;
}

bool ConfigManager::store()
{
    std::ofstream file(m_fileName);
    std::cout << "Storing configuration..." << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_fileName << std::endl;
        return false;
    }

    auto writeModel = [&](const auto& model)
    {
        for (const auto& [key, value] : model.getAllEntries())
        {
            file << key << cConfigAssignDelimiter << value << "\n";
        }
    };

    writeModel(m_controlConfig);
    writeModel(m_serialConfig);
    writeModel(m_logConfig);

    file.close();
    std::cout << "Store configuration done." << std::endl;
    return true;
}

void ConfigManager::defaultConfigStore()
{
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set default control configuration
    m_controlConfig.add(m_controlConfig.toString(ModelControl::ModelControlKey::Enable), cConfigDefaultControlEnable);
    m_controlConfig.add(m_controlConfig.toString(ModelControl::ModelControlKey::Mode), cConfigDefaultControlMode);
    m_controlConfig.add(m_controlConfig.toString(ModelControl::ModelControlKey::Toggle), cConfigDefaultControlToggle);
    m_controlConfig.add(m_controlConfig.toString(ModelControl::ModelControlKey::Timer), cConfigDefaultControlTimer);
    m_controlConfig.add(m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable), cConfigDefaultControlTimerEnable);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set default serial configuration
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Device), cConfigDefaultSerialDevice);
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud), cConfigDefaultSerialBaud);
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Data), cConfigDefaultSerialData);
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity), cConfigDefaultSerialParity);
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop), cConfigDefaultSerialStop);
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow), cConfigDefaultSerialFlow);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set default log configuration
    m_logConfig.add(m_logConfig.toString(ModelLog::ModelLogKey::FilePath), cConfigDefaultLogFilePath);
    m_logConfig.add(m_logConfig.toString(ModelLog::ModelLogKey::LogLevel), cConfigDefaultLogLevel);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Store default configuration to file
    store();
}
