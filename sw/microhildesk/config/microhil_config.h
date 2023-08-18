/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config.h
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
#pragma once

#include <glibmm.h>
#include <glibmm/keyfile.h>
#include "microhil_config_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILConfig class declaration and definition 
class MicroHILConfig : public AbMicroHILConfig
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILConfig constructor
    MicroHILConfig();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILConfig destructor
    ~MicroHILConfig() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load configuration from file
    /// @return boolean status true for success else false
    bool load() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validate configuration (existing all expected parameters)
    /// @return boolean status true for success else false
    bool validate() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting serial device file path from configuration
    /// @return file path for serial device
    Glib::ustring getDevice() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting baud rate for serial port from configuration
    /// @return integer value for serial port baud rate
    int getBaudRate() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting data bits for serial port from configuration
    /// @return integer value for data bits for charachter
    int getDataBits() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting parity for serial port from configuration
    /// @return parity type for the serial port
    Glib::ustring getParity() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting stop bits for serial port from configuration
    /// @return integer number of stop bits for the serial port
    int getStopBits() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log level
    /// @return log level
    Glib::ustring getLogLevel() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log path
    /// @return log path
    Glib::ustring getLogPath() const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Checking existence of configuration file
    /// @return boolean status true for existing else false
    bool checkConfigPath();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Home directory path
    std::string m_homePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration file path 
    std::string m_configFilePath{};
    
    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    Glib::KeyFile m_configuration{};
};
