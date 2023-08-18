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
    constexpr const int kConfigSerialLength{9};

    ////////////////////////////////////////////////////////////////////////
    /// Serial configuration section 
    constexpr const char kConfigSerialSection[]{"serial"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial device configuration parameter
    constexpr const char kConfigSerialDevice[]{"device"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial baud rate configuration parameter
    constexpr const char kConfigSerialBaudRate[]{"baud_rate"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial data bits configuration parameter
    constexpr const char kConfigSerialDataBits[]{"data_bits"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial parity configuration parameter
    constexpr const char kConfigSerialParity[]{"parity"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial stop bits configuration parameter
    constexpr const char kConfigSerialStopBits[]{"stop_bits"};

    ////////////////////////////////////////////////////////////////////////
    /// Log configuration section
    constexpr const char kConfigLogSection[]{"log"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter
    constexpr const char kConfigLogLevel[]{"level"};

    ////////////////////////////////////////////////////////////////////////
    /// Log file path configuration parameter
    constexpr const char kConfigLogFile[]{"file"};

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

    return true;
}

bool MicroHILConfig::validate()
{
    if(!isPreValid())
    {
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Checking configuration parameters
    auto configCheck = (
        m_configuration.has_key(kConfigSerialSection, kConfigSerialDevice) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialBaudRate) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialDataBits) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialParity) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialStopBits) &&
        m_configuration.has_key(kConfigLogSection, kConfigLogLevel) &&
        m_configuration.has_key(kConfigLogSection, kConfigLogFile)
    );

    if(!configCheck)
    {
        return false;
    }

    return true;
}

Glib::ustring MicroHILConfig::getDevice() const
{
    return m_configuration.get_string(
        kConfigSerialSection, kConfigSerialDevice
    );
}

int MicroHILConfig::getBaudRate() const
{
    return m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialBaudRate
    );
}

int MicroHILConfig::getDataBits() const
{
    return m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialDataBits
    );
}

Glib::ustring MicroHILConfig::getParity() const
{
    return m_configuration.get_string(
        kConfigSerialSection, kConfigSerialParity
    );
}

int MicroHILConfig::getStopBits() const
{
    return (int) m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialStopBits
    );
}

Glib::ustring MicroHILConfig::getLogLevel() const
{
    return m_configuration.get_string(kConfigLogSection, kConfigLogLevel);
}

Glib::ustring MicroHILConfig::getLogPath() const
{
    return m_configuration.get_string(kConfigLogSection, kConfigLogFile);
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
        for (int i = 0; i < kConfigSerialLength; i++)
        {
            defaultConfig << kConfigSerialDefault[i] << "\n";
        }
        defaultConfig.close();
    }

    return true;
}
