/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config_abstract.h
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

#include <glibmm/ustring.h>

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILConfig class declaration and definition
class AbMicroHILConfig
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILConfig destructor
    virtual ~AbMicroHILConfig() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load configuration
    /// @return boolean status true for success else false
    virtual bool load() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validate configuration (existing all expected parameters)
    /// @return boolean status true for success else false
    virtual bool validate() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set pre-validation state (existing configuration)
    /// @param configValid boolean indicator for existing configuration
    void setPreValid(bool configValid) {m_configPreValidate = configValid;}

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check is pre-validation state (existing configuration)
    /// @return boolean status true for valid else false
    bool isPreValid() const {return m_configPreValidate;};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting serial device file path from configuration
    /// @return file path for serial device
    virtual Glib::ustring getDevice() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting baud rate for serial port from configuration
    /// @return integer value for serial port baud rate
    virtual int getBaudRate() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting data bits for serial port from configuration
    /// @return integer value for data bits for charachter
    virtual int getDataBits() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting parity for serial port from configuration
    /// @return parity type for the serial port
    virtual Glib::ustring getParity() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting stop bits for serial port from configuration
    /// @return integer number of stop bits for the serial port
    virtual int getStopBits() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log level
    /// @return log level
    virtual Glib::ustring getLogLevel() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log path
    /// @return log path
    virtual Glib::ustring getLogPath() const = 0;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Pre-validation flag for configuration
    bool m_configPreValidate{false};
};
