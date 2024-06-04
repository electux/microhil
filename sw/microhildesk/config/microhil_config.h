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

#include "microhil_iconfig.h"
#include <glibmm/keyfile.h>

////////////////////////////////////////////////////////////////////////////
/// @brief MHConfig class is implementation for configuration mechanism
class MHConfig : public IMHConfig
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHConfig constructor
    explicit MHConfig();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHConfig destructor
    inline ~MHConfig() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded log configuration
    /// @return Signal for loaded log configuration
    SigLogConfig LogConfigLoaded() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded serial configuration
    /// @return Signal for loaded serial configuration
    SigSerialConfig SerialConfigLoaded() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks is pre-validation state (existing configuration)
    /// @return status true for success pre-validation else false
    bool isPreValid() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Loads configuration
    /// @return status true for success load configuration else false
    bool load() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Stores configuration
    /// @return status true for success store configuration else false
    bool store() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates configuration (existing all expected parameters)
    /// @return status true for success configuration validation else false
    bool validate() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets serial device file path to configuration
    /// @param device represents file path for the serial device
    void setDevice(const UString &device) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets serial device file path from configuration
    /// @return file path for the serial device
    UString getDevice() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets baud-rate for serial port to configuration
    /// @param baudRate represents baud-rate for the serial port
    void setBaudRate(const int baudRate) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets baud-rate for serial port from configuration
    /// @return integer value for serial port baud-rate
    int getBaudRate() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets data-bits for the serial port to configuration
    /// @param dataBits represents data-bits for the serial port
    void setDataBits(const int dataBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets data-bits for the serial port from configuration
    /// @return integer value for data-bits for charachter
    int getDataBits() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets parity for the serial port to configuration
    /// @param parity represents parity for the serial port
    void setParity(const int parity) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets parity for the serial port from configuration
    /// @return parity type for the serial port
    UString getParity() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets stop-bits for the serial port to configuration
    /// @param stopBits represents stop-bits for the serial port
    void setStopBits(const int stopBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets stop-bits for serial port from configuration
    /// @return integer number of stop-bits for the serial port
    int getStopBits() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represents log level for log settings
    void setLogLevel(const int level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log level
    /// @return log level
    UString getLogLevel() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log path
    /// @param path represents log file path for log messages
    void setLogPath(const UString &path) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log path
    /// @return log path
    UString getLogPath() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity to integer format (from config file)
    /// @param parity represents parity in string format (from config file)
    /// @return parity in integer format (to combobox index)
    int parityUnicodeStringToInt(const UString &parity);

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets pre-validation state (existing configuration)
    /// @param configValid represents indicator for existing configuration
    void setPreValid(bool configValid) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks existence of configuration file
    /// @return status true for existing configuration else false
    bool checkConfigPath() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts integer log level to string format
    /// @param logLevel represents log level in integer format
    /// @return string format of log level
    UString logLevelToUnicodeString(const int logLevel);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level in strong format to integer
    /// @param level represents log level in string format
    /// @return log level in integer format
    int logLevelStringToInt(const UString &level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares baud-rate (to config file)
    /// @param baudRate represents baud-rate for serial port (combobox index)
    /// @return baud-rate for the serial port in integer format
    int intToBaudRate(int baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares baud-rate (from config file)
    /// @param baudRate represents baud-rate from config file
    /// @return index for combobox
    int baudRateToInt(int baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Processes and prepares data-bits (from config file)
    /// @param dataBits represents data-bits from config file
    /// @return index for combobox
    int dataBitsToInt(int dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts combobox index to data-bits (to config file)
    /// @param dataBits represents data-bits for serial port (index combobox)
    /// @return data-bits for the serial port in integer format
    int intToDataBits(int dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts integer parity to string format (to config file)
    /// @param parity represents index combobox
    /// @return string format of parity in string format
    UString parityToUnicodeString(const int parity);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits to integer (from config file)
    /// @param dataBits represents data-bits from config file
    /// @return stop-bits in integer format (index combobox)
    int stopBitsToInt(int stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts combobox index to data-bits (to config file)
    /// @param dataBits represents data-bits index from combobox
    /// @return data-bits in integer format
    int intToStopBits(int stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates log configuration (existing expected parameters)
    /// @return status true for success validation else false
    bool validateLogSettings();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validates serial configuration (existing expected parameters)
    /// @return status true for success validation else false
    bool validateSerialSettings();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration home directory path
    std::string m_homePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration file path
    std::string m_configFilePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Pre-validation flag for checking configuration
    bool m_configPreValidate{false};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    Glib::KeyFile m_config{};

    ////////////////////////////////////////////////////////////////////////
    /// Signal for loaded log configuration from file
    SigLogConfig m_logConfig{};

    ////////////////////////////////////////////////////////////////////////
    /// Signal for loaded serial configuration from file
    SigSerialConfig m_serialConfig{};
};
