/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_iconfig.h
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

#include <sigc++/sigc++.h>
#include "../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for the serial port parity
enum class ParityConfig : int
{
    /// @brief Parity None
    MICROHIL_NONE_CONFIG = 0,
    /// @brief Parity Odd
    MICROHIL_ODD_CONFIG = 1,
    /// @brief Parity Even
    MICROHIL_EVEN_CONFIG = 2,
    /// @brief Parity Mark
    MICROHIL_MARK_CONFIG = 3,
    /// @brief Parity Space
    MICROHIL_SPACE_CONFIG = 4
};

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for the log levels
enum class LogLevelConfig : int
{
    /// @brief Log level info
    MICROHIL_INFO_CONFIG = 0,
    /// @brief Log level warning
    MICROHIL_WARNING_CONFIG = 1,
    /// @brief Log level error
    MICROHIL_ERROR_CONFIG = 2
};

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for loaded log configuration from file
using SigLogConfig = sigc::signal<void(MHString &, int)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for loaded serial configuration from file
using SigSerialConfig = sigc::signal<void(MHString &, MHVecUInt &)>;

////////////////////////////////////////////////////////////////////////////
/// @brief IMHConfig class is interface set for configuration mechanism
class IMHConfig
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHConfig destructor
    inline virtual ~IMHConfig() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded log configuration
    /// @return Signal for loaded log configuration
    virtual SigLogConfig LogConfigLoaded() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded serial configuration
    /// @return Signal for loaded serial configuration
    virtual SigSerialConfig SerialConfigLoaded() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets pre-validation state (existing configuration)
    /// @param configValid represents indicator for existing configuration
    virtual void setPreValid(bool configValid) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks is pre-validation state (existing configuration)
    /// @return status true for success pre-validation else false
    virtual bool isPreValid() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Loads configuration
    /// @return status true for success load configuration else false
    virtual bool load() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Stores configuration
    /// @return status true for success store configuration else false
    virtual bool store() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates configuration (existing all expected parameters)
    /// @return status true for success configuration validation else false
    virtual bool validate() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets serial device file path to configuration
    /// @param device represents file path for the serial device
    virtual void setDevice(const MHString &device) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets serial device file path from configuration
    /// @return file path for the serial device
    virtual MHString getDevice() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets baud-rate for serial port to configuration
    /// @param baudRate represents baud-rate for the serial port
    virtual void setBaudRate(const int baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets baud-rate for serial port from configuration
    /// @return integer value for serial port baud-rate
    virtual int getBaudRate() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets data-bits for the serial port to configuration
    /// @param dataBits represents data-bits for the serial port
    virtual void setDataBits(const int dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets data-bits for the serial port from configuration
    /// @return integer value for data-bits for charachter
    virtual int getDataBits() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets parity for the serial port to configuration
    /// @param parity represents parity for the serial port
    virtual void setParity(const int parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets parity for the serial port from configuration
    /// @return parity type for the serial port
    virtual MHString getParity() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets stop-bits for the serial port to configuration
    /// @param stopBits represents stop-bits for the serial port
    virtual void setStopBits(const int stopBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets stop-bits for serial port from configuration
    /// @return integer number of stop-bits for the serial port
    virtual int getStopBits() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represents log level for log settings
    virtual void setLogLevel(const int level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log level
    /// @return log level
    virtual MHString getLogLevel() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log path
    /// @param path represents log file path for log messages
    virtual void setLogPath(const MHString &path) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log path
    /// @return log path
    virtual MHString getLogPath() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks existence of configuration file
    /// @return status true for existing configuration else false
    virtual bool checkConfigPath() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts integer log level to string format
    /// @param logLevel represents log level in integer format
    /// @return string format of log level
    virtual MHString logLevelToUnicodeString(const int logLevel) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level in strong format to integer
    /// @param level represents log level in string format
    /// @return log level in integer format
    virtual int logLevelStringToInt(const MHString &level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares baud-rate (to config file)
    /// @param baudRate represents baud-rate for serial port (combobox index)
    /// @return baud-rate for the serial port in integer format
    virtual int intToBaudRate(int baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares baud-rate (from config file)
    /// @param baudRate represents baud-rate from config file
    /// @return index for combobox
    virtual int baudRateToInt(int baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares data-bits (from config file)
    /// @param dataBits represents data-bits from config file
    /// @return index for combobox
    virtual int dataBitsToInt(int dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts combobox index to data-bits (to config file)
    /// @param dataBits represents data-bits for serial port (index combobox)
    /// @return data-bits for the serial port in integer format
    virtual int intToDataBits(int dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts integer parity to string format (to config file)
    /// @param parity represents index combobox
    /// @return string format of parity in string format
    virtual MHString parityToUnicodeString(const int parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity to integer format (from config file)
    /// @param parity represents parity in string format (from config file)
    /// @return parity in integer format (to combobox index)
    virtual int parityUnicodeStringToInt(const MHString &parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits to integer (from config file)
    /// @param dataBits represents data-bits from config file
    /// @return stop-bits in integer format (index combobox)
    virtual int stopBitsToInt(int stopBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts combobox index to data-bits (to config file)
    /// @param dataBits represents data-bits index from combobox
    /// @return data-bits in integer format
    virtual int intToStopBits(int stopBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates log configuration (existing expected parameters)
    /// @return status true for success validation else false
    virtual bool validateLogSettings() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates serial configuration (existing expected parameters)
    /// @return status true for success validation else false
    virtual bool validateSerialSettings() = 0;
};
