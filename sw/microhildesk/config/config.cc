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
    ///   config_file - program configuration file name
    constexpr const char config_file[]{"/.microhil/config"};
};

using namespace Electux::App::Config;
using namespace Electux::App::Model;

Config::Config() : m_file_name{Glib::get_home_dir() + config_file}
{
}

bool Config::load()
{
    std::ifstream file(m_file_name);

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_file_name << std::endl;
        return false;
    }

    std::string line;
    std::unordered_map<std::string, std::string> config_map;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            config_map[key] = value;
        }
    }

    file.close();
    m_serial_config.add("device", config_map["device"]);
    m_serial_config.add("baud", config_map["baud"]);
    m_serial_config.add("data", config_map["data"]);
    m_serial_config.add("parity", config_map["parity"]);
    m_serial_config.add("stop", config_map["stop"]);

    return true;
}

bool Config::store()
{
    std::ofstream file(m_file_name);

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_file_name << std::endl;
        return false;
    }

    file << "device=" << m_serial_config.get_entity("device") << std::endl;
    file << "baud=" << m_serial_config.get_entity("baud") << std::endl;
    file << "data=" << m_serial_config.get_entity("data") << std::endl;
    file << "parity=" << m_serial_config.get_entity("parity") << std::endl;
    file << "stop=" << m_serial_config.get_entity("stop") << std::endl;
    file.close();

    return true;
}
