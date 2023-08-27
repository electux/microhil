/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config.cc
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <fstream>
#include <iostream>
#include <filesystem>
#include <glibmm/miscutils.h>
#include "microhil_config.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Configuration directory name
    constexpr const char kHomeDirName[]{"/.microhil/"};

    ////////////////////////////////////////////////////////////////////////
    /// Configuration file name
    constexpr const char kConfigFileName[]{"config"};

    ////////////////////////////////////////////////////////////////////////
    /// Number of lines in configurtion file
    constexpr const int kConfigLength{9};

    ////////////////////////////////////////////////////////////////////////
    /// Default configuration
    constexpr const char* kConfigSerialDefault[]
    {
        "[log]",
        "level=INFO",
        "file=/tmp/microhil.log",
        "[serial]",
        "device=/dev/ttyUSB0",
        "baud_rate=115200",
        "data_bits=8",
        "parity=None",
        "stop_bits=1"
    };
}

MicroHILConfig::MicroHILConfig()
{
    ////////////////////////////////////////////////////////////////////////
    /// Setup expected paths for home directory and configuration file
    m_homePath = Glib::get_home_dir() + kHomeDirName;
    m_configFilePath = m_homePath + kConfigFileName;

    ////////////////////////////////////////////////////////////////////////
    /// Pre-validation of configuration path
    setPreValid(checkConfigPath());
}

bool MicroHILConfig::load()
{
    ////////////////////////////////////////////////////////////////////////
    /// Load configuration from file 
    auto loadedConfig = m_configuration.load_from_file(m_configFilePath);

    ////////////////////////////////////////////////////////////////////////
    /// Validation of loaded configuration
    auto validatedConfig = validate(); 

    if(!loadedConfig || !validatedConfig)
    {
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Emit signal for loaded log configuration
    m_logConfiguration.emit(
        getLogPath(),
        logLevelStringToInt(getLogLevel())
    );
    
    ////////////////////////////////////////////////////////////////////////
    /// Emit signal for loaded serial configuration
    m_serialConfiguration.emit(
        getDevice(),
        getBaudRate(),
        getDataBits(),
        parityStringToInt(getParity()),
        getStopBits()
    );

    return true;
}

bool MicroHILConfig::store()
{
    return m_configuration.save_to_file(m_configFilePath);
}

bool MicroHILConfig::validate()
{
    if(!isPreValid())
    {
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Checking configuration parameters
    auto configLogCheck = validateLogSettings();
    auto configSerialCheck = validateSerialSettings();

    if(!configLogCheck || !configSerialCheck)
    {
        return false;
    }

    return true;
}

bool MicroHILConfig::checkConfigPath()
{
    ////////////////////////////////////////////////////////////////////////
    // Check home directory /home/<username>/.microhil/
    std::filesystem::directory_entry homeDirEntry{m_homePath};
    auto homeDirExists = homeDirEntry.exists();

    if(!homeDirExists)
    {
        if(!std::filesystem::create_directory(m_homePath))
        {
            return false;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    // Check config file in case of missing generate new with default setup
    // Configuration file location: /home/<username>/.microhil/config
    auto configFileExists = std::filesystem::exists(m_configFilePath);

    if(!configFileExists)
    {
        std::ofstream defaultConfig(m_configFilePath);

        for (int i = 0; i < kConfigLength; i++)
        {
            defaultConfig << kConfigSerialDefault[i] << "\n";
        }

        defaultConfig.close();
    }

    return true;
}
