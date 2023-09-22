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
    /// Serial port data-bits offset configuration parameter
    constexpr const int kConfigDataBitsOffset{5};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port stop-bits offset configuration parameter
    constexpr const int kConfigStopBitsOffset{1};

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
    /// Serial port parity NONE combobox item index id
    constexpr const int kConfigParityNoneId{0};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity ODD combobox item index id
    constexpr const int kConfigParityOddId{1};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity EVEN combobox item index id
    constexpr const int kConfigParityEvenId{2};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity MARK combobox item index id
    constexpr const int kConfigParityMarkId{3};

    ////////////////////////////////////////////////////////////////////////
    /// Serial port parity SPACE combobox item index id
    constexpr const int kConfigParitySpaceId{4};
}

int MHConfig::baudRateToInt(int baudRate)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert baud-rate to index item for combobox
    switch (baudRate)
    {
    case 110:
        return 0;
    case 300:
        return 1;
    case 600:
        return 2;
    case 1200:
        return 3;
    case 2400:
        return 4;
    case 4800:
        return 5;
    case 9600:
        return 6;
    case 14400:
        return 7;
    case 19200:
        return 8;
    case 38400:
        return 9;
    case 57600:
        return 10;
    case 115200:
        return 11;
    case 128000:
        return 12;
    case 256000:
        return 13;
    }

    return 115200;
}

int MHConfig::intToBaudRate(int baudRate)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert index item of combobox to baud-rate
    switch (baudRate)
    {
    case 0:
        return 110;
    case 1:
        return 300;
    case 2:
        return 600;
    case 3:
        return 1200;
    case 4:
        return 2400;
    case 5:
        return 4800;
    case 6:
        return 9600;
    case 7:
        return 14400;
    case 8:
        return 19200;
    case 9:
        return 38400;
    case 10:
        return 57600;
    case 11:
        return 115200;
    case 12:
        return 128000;
    case 13:
        return 256000;
    }

    return 115200;
}

int MHConfig::dataBitsToInt(int dataBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process data-bits to index item of combobox
    return (dataBits - kConfigDataBitsOffset);
}

int MHConfig::intToDataBits(int dataBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process index item of combobox to data-bits
    return (dataBits + kConfigDataBitsOffset);
}

MHString MHConfig::parityToUnicodeString(const int parity)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert integer parity to scopped enumerator class
    auto parityPrepared = static_cast<ParityConfig>(parity);

    switch (parityPrepared)
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

int MHConfig::parityUnicodeStringToInt(const MHString &parity)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert string format of parity to index item for combobox
    if (parity == kConfigParityOdd)
    {
        return kConfigParityOddId;
    }

    if (parity == kConfigParityEven)
    {
        return kConfigParityEvenId;
    }

    if (parity == kConfigParityMark)
    {
        return kConfigParityMarkId;
    }

    if (parity == kConfigParitySpace)
    {
        return kConfigParitySpaceId;
    }

    return kConfigParityNoneId;
}

int MHConfig::stopBitsToInt(int stopBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process stop-bits to index item for combobox
    return (stopBits - kConfigStopBitsOffset);
}

int MHConfig::intToStopBits(int stopBits)
{
    ////////////////////////////////////////////////////////////////////////
    /// Pre-process index item from combobox to stop-bits
    return (stopBits + kConfigStopBitsOffset);
}
