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
    /// @brief Signal for loaded log configuration
    /// @return Signal for loaded log configuration
    logConfiguration logConfigurationLoaded() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for loaded serial configuration
    /// @return Signal for loaded serial configuration
    serialConfiguration serialConfigurationLoaded() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Load configuration from file
    /// @return boolean status true for success else false
    bool load() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Store configuration
    /// @return boolean status true for success else false
    bool store() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validate configuration (existing all expected parameters)
    /// @return boolean status true for success else false
    bool validate() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting serial device file path to configuration
    /// @param device file path
    void setDevice(Glib::ustring device) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting serial device file path from configuration
    /// @return file path for serial device
    Glib::ustring getDevice() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting baud rate for serial port to configuration
    /// @param baudRate for serial port
    void setBaudRate(int baudRate) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting baud rate for serial port from configuration
    /// @return integer value for serial port baud rate
    int getBaudRate() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting data bits for serial port to configuration
    /// @param dataBits for serial port
    void setDataBits(int dataBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting data bits for serial port from configuration
    /// @return integer value for data bits for charachter
    int getDataBits() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting parity for serial port to configuration
    /// @param parity for serial port
    void setParity(int parity) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting parity for serial port from configuration
    /// @return parity type for the serial port
    Glib::ustring getParity() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting stop bits for serial port to configuration
    /// @param stopBits for serial port
    void setStopBits(int stopBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting stop bits for serial port from configuration
    /// @return integer number of stop bits for the serial port
    int getStopBits() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting log level
    /// @param level for log settings
    void setLogLevel(int level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log level
    /// @return log level
    Glib::ustring getLogLevel() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting log path
    /// @param path for log messages
    void setLogPath(Glib::ustring path) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log path
    /// @return log path
    Glib::ustring getLogPath() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Checking existence of configuration file
    /// @return boolean status true for existing else false
    bool checkConfigPath();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert integer log level to string format
    /// @param logLevel in integer format
    /// @return string format of log level
    Glib::ustring logLevelToUnicodeString(int logLevel);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert log level in strong format to integer
    /// @param level in string format
    /// @return log level in integer format
    int logLevelStringToInt(Glib::ustring level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Process and prepare baud rate (to config file)
    /// @param baudRate for serial port (combobox index)
    /// @return baud rate for serial port in integer format
    int intToBaudRate(int baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Process and prepare baud rate (from config file)
    /// @param baudRate value from config file
    /// @return index for combobox
    int baudRateToInt(const int baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Process and prepare data bits (from config file)
    /// @param dataBits value from config file
    /// @return index for combobox
    int dataBitsToInt(int dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert combobox index to data bits (to config file)
    /// @param dataBits for serial port (index combobox)
    /// @return data bits for serial port in integer format
    int intToDataBits(int dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert integer parity to string format (to config file)
    /// @param parity index combobox
    /// @return string format of parity in string format
    Glib::ustring parityToUnicodeString(int parity);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert parity to integer format (from config file)
    /// @param parity in string format (from config file)
    /// @return parity in integer format (to combobox index)
    int parityUnicodeStringToInt(Glib::ustring parity);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert stop-bits to integer (from config file)
    /// @param dataBits from config file
    /// @return stop-bits in integer format (index combobox)
    int stopBitsToInt(int stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert combobox index to data-bits (to config file)
    /// @param dataBits index from combobox
    /// @return data-bits in integer format
    int intToStopBits(int stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validate log configuration (existing expected parameters)
    /// @return boolean status true for success else false
    bool validateLogSettings();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Validate serial configuration (existing expected parameters)
    /// @return boolean status true for success else false
    bool validateSerialSettings();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Home directory path
    std::string m_homePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration file path 
    std::string m_configFilePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    Glib::KeyFile m_configuration{};

    ////////////////////////////////////////////////////////////////////////
    /// Signal for loaded log configuration from file
    logConfiguration m_logConfiguration{};

    ////////////////////////////////////////////////////////////////////////
    /// Signal for loaded serial configuration from file
    serialConfiguration m_serialConfiguration{};
};
