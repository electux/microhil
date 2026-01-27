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
#include "config_manager.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration parameters
    ///   configFile - program configuration file name
    ///   configAssignDelimiter - delimiter for key-value assignment
    ///   configCommentChar - character for comment line
    constexpr std::string_view configFile{".microhil/config"};
    constexpr char configAssignDelimiter{'='};
    constexpr char configCommentChar{'#'};
};

using namespace Electux::App::Config;
using namespace Electux::App::Model;

ConfigManager::ConfigManager()
{
    m_fileName = Glib::build_filename(Glib::get_home_dir(), configFile.data());
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

void ConfigManager::setSerialConfig(const ModelSerial& config)
{
    m_serialConfig = config;
}

void ConfigManager::setLogConfig(const ModelLog& config)
{
    m_logConfig = config;
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
        if (line.empty() || line[0] == configCommentChar)
        {
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, configAssignDelimiter) && std::getline(iss, value))
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
            file << key << configAssignDelimiter << value << "\n";
        }
    };

    writeModel(m_serialConfig);
    writeModel(m_logConfig);

    file.close();
    std::cout << "Store configuration done." << std::endl;
    return true;
}

void ConfigManager::defaultConfigStore()
{
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set default serial configuration
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Device), "/dev/ttyUSB0");
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Baud), "10");
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Data), "3");
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Parity), "2");
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Stop), "0");
    m_serialConfig.add(m_serialConfig.toString(ModelSerial::ModelSerialKey::Flow), "0");

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set default log configuration
    m_logConfig.add(m_logConfig.toString(ModelLog::ModelLogKey::FilePath), "/tmp/microhildesk.log");
    m_logConfig.add(m_logConfig.toString(ModelLog::ModelLogKey::LogLevel), "2");

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Store default configuration to file
    store();
}
