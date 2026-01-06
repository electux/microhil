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
    constexpr std::string_view configFile{".microhil/config"};
};

using namespace Electux::App::Config;
using namespace Electux::App::Model;

Config::Config()
{
    m_fileName = Glib::build_filename(Glib::get_home_dir(), configFile.data());
    std::cout << "Setup configuration file path: " << m_fileName << std::endl;
}

const ModelSerial& Config::getSerialConfig() const
{
    return m_serialConfig; 
}

const ModelLog& Config::getLogConfig() const
{
    return m_logConfig;
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
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
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

bool Config::store()
{
    std::ofstream file(m_fileName);
    std::cout << "Store configuration..." << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << m_fileName << std::endl;
        return false;
    }

    auto writeModel = [&](const auto& model)
    {
        for (const auto& [key, value] : model.getAllEntries())
        {
            file << key << "=" << value << "\n";
        }
    };

    writeModel(m_serialConfig);
    writeModel(m_logConfig);

    file.close();
    std::cout << "Store configuration done." << std::endl;
    return true;
}
