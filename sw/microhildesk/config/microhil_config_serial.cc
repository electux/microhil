/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config_serial.cc
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
#include "microhil_config.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Serial configuration section
    constexpr const char kConfigSerial[]{"serial"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial device configuration parameter
    constexpr const char kConfigDevice[]{"device"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial baud-rate configuration parameter
    constexpr const char kConfigBaudRate[]{"baud_rate"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial data-bits configuration parameter
    constexpr const char kConfigDataBits[]{"data_bits"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial parity configuration parameter
    constexpr const char kConfigParity[]{"parity"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial stop-bits configuration parameter
    constexpr const char kConfigStopBits[]{"stop_bits"};
} // namespace

void MHConfig::setDevice(const UString &device)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets the serial port device to configuration
    m_config.set_string(kConfigSerial, kConfigDevice, device);
}

UString MHConfig::getDevice() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets the serial port device from configuration
    return m_config.get_string(kConfigSerial, kConfigDevice);
}

void MHConfig::setBaudRate(const int baudRate)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process baud-rate for configuration file
    auto baudRatePrepared = intToBaudRate(baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// Sets the serial port baud-rate to configuration
    m_config.set_integer(kConfigSerial, kConfigBaudRate, baudRatePrepared);
}

int MHConfig::getBaudRate()
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets the serial port baud-rate from configuration
    auto baudRate = m_config.get_integer(kConfigSerial, kConfigBaudRate);

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process baud-rate from configuration file
    return baudRateToInt(baudRate);
}

void MHConfig::setDataBits(const int dataBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process data-bits for configuration file
    auto dataBitsPrepared = intToDataBits(dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// Sets the serial port data-bits to configuration
    m_config.set_integer(kConfigSerial, kConfigDataBits, dataBitsPrepared);
}

int MHConfig::getDataBits()
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets the serial port data-bits from configuration
    auto dataBits = m_config.get_integer(kConfigSerial, kConfigDataBits);

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process data-bits from configuration file
    return dataBitsToInt(dataBits);
}

void MHConfig::setParity(const int parity)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process parity for configuration file
    auto parityPrepared = parityToUnicodeString(parity);

    ////////////////////////////////////////////////////////////////////////
    /// Sets the serial port parity to configuration
    m_config.set_string(kConfigSerial, kConfigParity, parityPrepared);
}

UString MHConfig::getParity() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets the serial port parity from configuration
    return m_config.get_string(kConfigSerial, kConfigParity);
}

void MHConfig::setStopBits(const int stopBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process stop-bits for configuration file
    const auto stopBitsPrepared = intToStopBits(stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// Sets the serial port stop-bits to configuration
    m_config.set_integer(kConfigSerial, kConfigStopBits, stopBitsPrepared);
}

int MHConfig::getStopBits()
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets the serial port stop-bits from configuration
    auto stopBits = (int)m_config.get_integer(kConfigSerial, kConfigStopBits);

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process stop-bits from configuration file
    return stopBitsToInt(stopBits);
}

bool MHConfig::validateSerialSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checking serial configuration parameters from config file
    const auto configCheck =
        (m_config.has_key(kConfigSerial, kConfigDevice) &&
         m_config.has_key(kConfigSerial, kConfigBaudRate) &&
         m_config.has_key(kConfigSerial, kConfigDataBits) &&
         m_config.has_key(kConfigSerial, kConfigParity) &&
         m_config.has_key(kConfigSerial, kConfigStopBits));

    if (!configCheck)
    {
        ////////////////////////////////////////////////////////////////////
        /// Configuration file, serial section corrupted
        return false;
    }

    return true;
}
