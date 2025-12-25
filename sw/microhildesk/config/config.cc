/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * config.cc
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
#include "config.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration parameters
    ///   configFile - program configuration file name
    constexpr const char configFile[]{".microhil/config"};
};

using namespace Electux::App::Config;
using namespace Electux::App::Model;

Config::Config() :
    m_fileName{Glib::build_filename(Glib::get_home_dir(), configFile)},
    m_serialConfig{ModelSerial()},
    m_logConfig{ModelLog()}
{
    std::cout << "Setup configuration file path: " << m_fileName << std::endl;
}

bool Config::load()
{
    std::ifstream file(m_fileName);

    std::cout << "Load configuration..." << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_fileName << std::endl;
        return false;
    }

    std::string line;
    std::unordered_map<std::string, std::string> configMap;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            if (!m_serialConfig.validateKey(key) && !m_logConfig.validateKey(key))
            {
                std::cerr << "Invalid configuration key: " << key << std::endl;
                return false;
            }
            configMap[key] = value;
        }
    }

    file.close();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load serial configuration
    std::initializer_list<ModelSerial::ModelSerialKey> serialKeys = {
        ModelSerial::ModelSerialKey::Device,
        ModelSerial::ModelSerialKey::Baud,
        ModelSerial::ModelSerialKey::Data,
        ModelSerial::ModelSerialKey::Parity,
        ModelSerial::ModelSerialKey::Stop
    };
    for (const auto key : serialKeys)
    {
        auto serialKey = m_serialConfig.toString(key);
        m_serialConfig.add(serialKey, configMap[serialKey]);
    }

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load log configuration
    auto logLevelKey = m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    m_logConfig.add(logLevelKey, configMap[logLevelKey]);

    std::cout << "Load configuration done." << std::endl;

    return true;
}

bool Config::store()
{
    std::ofstream file(m_fileName);

    std::cout << "Store configuration..." << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_fileName << std::endl;
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    /// @brief Store serial configuration
    std::initializer_list<ModelSerial::ModelSerialKey> serialKeys = {
        ModelSerial::ModelSerialKey::Device,
        ModelSerial::ModelSerialKey::Baud,
        ModelSerial::ModelSerialKey::Data,
        ModelSerial::ModelSerialKey::Parity,
        ModelSerial::ModelSerialKey::Stop
    };

    for (const auto key : serialKeys)
    {
        auto serialKey = m_serialConfig.toString(key);
        file << serialKey << "=" << m_serialConfig.getEntity(serialKey) << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////
    /// @brief Store log configuration
    auto logLevelKey = m_logConfig.toString(ModelLog::ModelLogKey::LogLevel);
    file << logLevelKey << "=" << m_logConfig.getEntity(logLevelKey) << std::endl;
    file.close();

    std::cout << "Store configuration done." << std::endl;

    return true;
}
