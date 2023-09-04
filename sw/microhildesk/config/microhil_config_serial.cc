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
    constexpr const char kConfigSerialSection[]{"serial"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial device configuration parameter
    constexpr const char kConfigSerialDevice[]{"device"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial baud-rate configuration parameter
    constexpr const char kConfigSerialBaudRate[]{"baud_rate"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial data-bits configuration parameter
    constexpr const char kConfigSerialDataBits[]{"data_bits"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial parity configuration parameter
    constexpr const char kConfigSerialParity[]{"parity"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial stop-bits configuration parameter
    constexpr const char kConfigSerialStopBits[]{"stop_bits"};
}

void MicroHILConfig::setDevice(const MHString device)
{
    m_config.set_string(kConfigSerialSection, kConfigSerialDevice, device);
}

MHString MicroHILConfig::getDevice()
{
    return m_config.get_string(kConfigSerialSection, kConfigSerialDevice);
}

void MicroHILConfig::setBaudRate(const int baudRate)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process baud-rate for configuration file
    auto baudRatePrepared = intToBaudRate(baudRate);

    m_config.set_integer(
        kConfigSerialSection, kConfigSerialBaudRate, baudRatePrepared
    );
}

int MicroHILConfig::getBaudRate()
{
    auto baudRate = m_config.get_integer(
        kConfigSerialSection, kConfigSerialBaudRate
    );

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process baud-rate from configuration file
    return baudRateToInt(baudRate);
}

void MicroHILConfig::setDataBits(const int dataBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process data-bits for configuration file
    auto dataBitsPrepared = intToDataBits(dataBits);

    m_config.set_integer(
        kConfigSerialSection, kConfigSerialDataBits, dataBitsPrepared
    );
}

int MicroHILConfig::getDataBits()
{
    auto dataBits = m_config.get_integer(
        kConfigSerialSection, kConfigSerialDataBits
    );

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process data-bits from configuration file
    return dataBitsToInt(dataBits);
}

void MicroHILConfig::setParity(const int parity)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process parity for configuration file
    auto parityPrepared = parityToUnicodeString(parity);

    m_config.set_string(
        kConfigSerialSection, kConfigSerialParity, parityPrepared
    );
}

MHString MicroHILConfig::getParity()
{
    return m_config.get_string(kConfigSerialSection, kConfigSerialParity);
}

void MicroHILConfig::setStopBits(const int stopBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process stop-bits for configuration file
    auto stopBitsPrepared = intToStopBits(stopBits);

    m_config.set_integer(
        kConfigSerialSection, kConfigSerialStopBits, stopBitsPrepared
    );
}

int MicroHILConfig::getStopBits()
{
    auto stopBits = (int)m_config.get_integer(
        kConfigSerialSection, kConfigSerialStopBits
    );

    ////////////////////////////////////////////////////////////////////////
    /// Pre-process stop-bits from configuration file
    return stopBitsToInt(stopBits);
}

bool MicroHILConfig::validateSerialSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checking serial configuration parameters from config file
    auto configCheck = (
        m_config.has_key(kConfigSerialSection, kConfigSerialDevice) &&
        m_config.has_key(kConfigSerialSection, kConfigSerialBaudRate) &&
        m_config.has_key(kConfigSerialSection, kConfigSerialDataBits) &&
        m_config.has_key(kConfigSerialSection, kConfigSerialParity) &&
        m_config.has_key(kConfigSerialSection, kConfigSerialStopBits)
    );

    if(!configCheck)
    {
        ////////////////////////////////////////////////////////////////////
        /// Configuration file, serial section corrupted
        return false;
    }

    return true;
}
