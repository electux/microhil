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
    /// Serial port parity NONE configuration parameter
    constexpr const char kConfigParityNone[]{"NONE"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity ODD configuration parameter
    constexpr const char kConfigParityOdd[]{"ODD"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity EVEN configuration parameter
    constexpr const char kConfigParityEven[]{"EVEN"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity MARK configuration parameter
    constexpr const char kConfigParityMark[]{"MARK"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity SPACE configuration parameter
    constexpr const char kConfigParitySpace[]{"SPACE"};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port data bits offset configuration parameter
    constexpr const int kConfigDataBitsOffset{5};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port stop bits offset configuration parameter
    constexpr const int kConfigStopBitsOffset{1};
}

void MicroHILConfig::setDevice(Glib::ustring device)
{
    m_configuration.set_string(
        kConfigSerialSection, kConfigSerialDevice, device
    );
}

Glib::ustring MicroHILConfig::getDevice() const
{
    return m_configuration.get_string(
        kConfigSerialSection, kConfigSerialDevice
    );
}

void MicroHILConfig::setBaudRate(int baudRate)
{
    auto baudRatePrepared = processBaudRate(baudRate);

    m_configuration.set_integer(
        kConfigSerialSection, kConfigSerialBaudRate, baudRatePrepared
    );
}

int MicroHILConfig::getBaudRate() const
{
    return m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialBaudRate
    );
}

void MicroHILConfig::setDataBits(int dataBits)
{
    auto dataBitsPrepared = dataBits + kConfigDataBitsOffset;

    m_configuration.set_integer(
        kConfigSerialSection, kConfigSerialDataBits, dataBitsPrepared
    );
}

int MicroHILConfig::getDataBits() const
{
    return m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialDataBits
    );
}

void MicroHILConfig::setParity(int parity)
{
    auto parityPrepared = parityToUnicodeString(parity);

    m_configuration.set_string(
        kConfigSerialSection, kConfigSerialParity, parityPrepared
    );
}

Glib::ustring MicroHILConfig::getParity() const
{
    return m_configuration.get_string(
        kConfigSerialSection, kConfigSerialParity
    );
}

void MicroHILConfig::setStopBits(int stopBits)
{
    auto stopBitsPrepared = stopBits + kConfigStopBitsOffset;

    m_configuration.set_integer(
        kConfigSerialSection, kConfigSerialStopBits, stopBitsPrepared
    );
}

int MicroHILConfig::getStopBits() const
{
    return (int) m_configuration.get_integer(
        kConfigSerialSection, kConfigSerialStopBits
    );
}

bool MicroHILConfig::validateSerialSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checking serial configuration parameters
    auto configCheck = (
        m_configuration.has_key(kConfigSerialSection, kConfigSerialDevice) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialBaudRate) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialDataBits) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialParity) &&
        m_configuration.has_key(kConfigSerialSection, kConfigSerialStopBits)
    );

    if(!configCheck)
    {
        return false;
    }

    return true;
}

int MicroHILConfig::processBaudRate(int baudRate)
{
    switch(baudRate)
    {
        case 0: return 110;
        case 1: return 300;
        case 2: return 600;
        case 3: return 1200;
        case 4: return 2400;
        case 5: return 4800;
        case 6: return 9600;
        case 7: return 14400;
        case 8: return 19200;
        case 9: return 38400;
        case 10: return 57600;
        case 11: return 115200;
        case 12: return 128000;
        case 13: return 256000;
    }

    return 115200;
}

Glib::ustring MicroHILConfig::parityToUnicodeString(int parity)
{
    auto parityPrepared = static_cast<ParityConfig>(parity);

    switch(parityPrepared)
    {
        case ParityConfig::MICROHIL_NONE_CONFIG:
            return kConfigParityNone;
        case ParityConfig::MICROHIL_ODD_CONFIG:
            return kConfigParityOdd;
        case ParityConfig::MICROHIL_EVEN_CONFIG:
            return kConfigParityEven;
        case ParityConfig::MICROHIL_MARK_CONFIG:
            return kConfigParityMark;
        case ParityConfig::MICROHIL_SPACE_CONFIG:
            return kConfigParitySpace;
    }

    return kConfigParityNone;
}
