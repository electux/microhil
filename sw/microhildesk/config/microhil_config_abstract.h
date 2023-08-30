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

#include <vector>
#include <sigc++/sigc++.h>
#include <glibmm/ustring.h>

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for serial port parity
enum class ParityConfig: int
{
    MICROHIL_NONE_CONFIG = 0,
    MICROHIL_ODD_CONFIG = 1,
    MICROHIL_EVEN_CONFIG = 2,
    MICROHIL_MARK_CONFIG = 3,
    MICROHIL_SPACE_CONFIG = 4
};

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for log levels
enum class LogLevelConfig: int
{
    MICROHIL_INFO_CONFIG = 0,
    MICROHIL_WARNING_CONFIG = 1,
    MICROHIL_ERROR_CONFIG = 2
};

////////////////////////////////////////////////////////////////////////////
/// @brief Declared type vector of int elements
using VectorUInt = std::vector<unsigned int>;

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILConfig class declaration and definition
class AbMicroHILConfig
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for loaded log configuration from file
    using SigLogConfig = sigc::signal<void(Glib::ustring, int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for loaded serial configuration from file
    using SigSerialConfig = sigc::signal<void(Glib::ustring, VectorUInt)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILConfig destructor
    virtual ~AbMicroHILConfig() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded log configuration
    /// @return Signal for loaded log configuration
    virtual SigLogConfig LogConfigLoaded() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded serial configuration
    /// @return Signal for loaded serial configuration
    virtual SigSerialConfig SerialConfigLoaded() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load configuration
    /// @return boolean status true for success else false
    virtual bool load() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Store configuration
    /// @return boolean status true for success else false
    virtual bool store() = 0;

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
    /// @brief Setting serial device file path to configuration
    /// @param device file path
    virtual void setDevice(const Glib::ustring device) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting serial device file path from configuration
    /// @return file path for serial device
    virtual Glib::ustring getDevice() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting baud rate for serial port to configuration
    /// @param baudRate for serial port
    virtual void setBaudRate(const int baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting baud rate for serial port from configuration
    /// @return integer value for serial port baud rate
    virtual int getBaudRate() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting data bits for serial port to configuration
    /// @param dataBits for serial port
    virtual void setDataBits(const int dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting data bits for serial port from configuration
    /// @return integer value for data bits for charachter
    virtual int getDataBits() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting parity for serial port to configuration
    /// @param parity for serial port
    virtual void setParity(const int parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting parity for serial port from configuration
    /// @return parity type for the serial port
    virtual Glib::ustring getParity() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting stop bits for serial port to configuration
    /// @param stopBits for serial port
    virtual void setStopBits(const int stopBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting stop bits for serial port from configuration
    /// @return integer number of stop bits for the serial port
    virtual int getStopBits() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting log level
    /// @param level for log settings
    virtual void setLogLevel(const int level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log level
    /// @return log level
    virtual Glib::ustring getLogLevel() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting log path
    /// @param path for log messages
    virtual void setLogPath(const Glib::ustring path) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log path
    /// @return log path
    virtual Glib::ustring getLogPath() = 0;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Pre-validation flag for configuration
    bool m_configPreValidate{false};
};
