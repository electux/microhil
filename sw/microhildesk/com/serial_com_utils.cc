/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com_utils.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "serial_com.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Expected serial parameters
    ///   baud-rate index values
    ///   data-bits index values
    ///   parity index values
    ///   stop-bits index values
    ///   invalid parameter for serial port
    constexpr const unsigned int comBaud110 = 0;
    constexpr const unsigned int comBaud300 = 1;
    constexpr const unsigned int comBaud600 = 2;
    constexpr const unsigned int comBaud1200 = 3;
    constexpr const unsigned int comBaud2400 = 4;
    constexpr const unsigned int comBaud4800 = 5;
    constexpr const unsigned int comBaud9600 = 6;
    constexpr const unsigned int comBaud19200 = 7;
    constexpr const unsigned int comBaud38400 = 8;
    constexpr const unsigned int comBaud57600 = 9;
    constexpr const unsigned int comBaud115200 = 10;
    constexpr const unsigned int comBaud230400 = 11;
    constexpr const unsigned int comDataBits5 = 0;
    constexpr const unsigned int comDataBits6 = 1;
    constexpr const unsigned int comDataBits7 = 2;
    constexpr const unsigned int comDataBits8 = 3; 
    constexpr const unsigned int comParityEven = 0;
    constexpr const unsigned int comParityOdd = 1;
    constexpr const unsigned int comParityNone = 2;
    constexpr const unsigned int comStopBits1 = 0;
    constexpr const unsigned int comStopBits2 = 1;
    constexpr const unsigned int comInvalidParameter = 127;
};

using namespace Electux::App::Com;

unsigned int SerialCom::baudToUint(const BaudRate baud)
{
    switch (baud)
    {
    case BaudRate::BAUD_50:
        return comInvalidParameter;
    case BaudRate::BAUD_75:
        return comInvalidParameter;
    case BaudRate::BAUD_110:
        return comBaud110;
    case BaudRate::BAUD_134:
        return comInvalidParameter;
    case BaudRate::BAUD_150:
        return comInvalidParameter;
    case BaudRate::BAUD_200:
        return comInvalidParameter;
    case BaudRate::BAUD_300:
        return comBaud300;
    case BaudRate::BAUD_600:
        return comBaud600;
    case BaudRate::BAUD_1200:
        return comBaud1200;
    case BaudRate::BAUD_1800:
        return comInvalidParameter;
    case BaudRate::BAUD_2400:
        return comBaud2400;
    case BaudRate::BAUD_4800:
        return comBaud4800;
    case BaudRate::BAUD_9600:
        return comBaud9600;
    case BaudRate::BAUD_19200:
        return comBaud19200;
    case BaudRate::BAUD_38400:
        return comBaud38400;
    case BaudRate::BAUD_57600:
        return comBaud57600;
    case BaudRate::BAUD_115200:
        return comBaud115200;
    case BaudRate::BAUD_230400:
        return comBaud230400;
    case BaudRate::BAUD_460800:
        return comInvalidParameter;
    case BaudRate::BAUD_500000:
        return comInvalidParameter;
    case BaudRate::BAUD_576000:
        return comInvalidParameter;
    case BaudRate::BAUD_921600:
        return comInvalidParameter;
    case BaudRate::BAUD_1000000:
        return comInvalidParameter;
    case BaudRate::BAUD_1152000:
        return comInvalidParameter;
    case BaudRate::BAUD_1500000:
        return comInvalidParameter;
    case BaudRate::BAUD_2000000:
        return comInvalidParameter;
    case BaudRate::BAUD_2500000:
        return comInvalidParameter;
    case BaudRate::BAUD_3000000:
        return comInvalidParameter;
    case BaudRate::BAUD_3500000:
        return comInvalidParameter;
    case BaudRate::BAUD_4000000:
        return comInvalidParameter;
    case BaudRate::BAUD_INVALID:
        return comInvalidParameter;
    }

    return comInvalidParameter;
}

BaudRate SerialCom::uintToBaud(const unsigned int baud)
{
    switch (baud)
    {
    case comBaud110:
        return BaudRate::BAUD_110;
    case comBaud300:
        return BaudRate::BAUD_300;
    case comBaud600:
        return BaudRate::BAUD_600;
    case comBaud1200:
        return BaudRate::BAUD_1200;
    case comBaud2400:
        return BaudRate::BAUD_2400;
    case comBaud4800:
        return BaudRate::BAUD_4800;
    case comBaud9600:
        return BaudRate::BAUD_9600;
    case comBaud19200:
        return BaudRate::BAUD_19200;
    case comBaud38400:
        return BaudRate::BAUD_38400;
    case comBaud57600:
        return BaudRate::BAUD_57600;
    case comBaud115200:
        return BaudRate::BAUD_115200;
    case comBaud230400:
        return BaudRate::BAUD_230400;
    }

    return BaudRate::BAUD_INVALID;
}

unsigned int SerialCom::dataBitsToUint(const CharacterSize data)
{
    switch (data)
    {
    case CharacterSize::CHAR_SIZE_5:
        return comDataBits5;
    case CharacterSize::CHAR_SIZE_6:
        return comDataBits6;
    case CharacterSize::CHAR_SIZE_7:
        return comDataBits7;
    case CharacterSize::CHAR_SIZE_8:
        return comDataBits8;
    case CharacterSize::CHAR_SIZE_INVALID:
        return comInvalidParameter;
    }

    return comInvalidParameter;
}

CharacterSize SerialCom::uintToDataBits(const unsigned int data)
{
    switch (data)
    {
    case comDataBits5:
        return CharacterSize::CHAR_SIZE_5;
    case comDataBits6:
        return CharacterSize::CHAR_SIZE_6;
    case comDataBits7:
        return CharacterSize::CHAR_SIZE_7;
    case comDataBits8:
        return CharacterSize::CHAR_SIZE_8;
    }

    return CharacterSize::CHAR_SIZE_INVALID;
}

unsigned int SerialCom::parityToUint(const Parity parity)
{
    switch (parity)
    {
    case Parity::PARITY_EVEN:
        return comParityEven;
    case Parity::PARITY_ODD:
        return comParityOdd;
    case Parity::PARITY_NONE:
        return comParityNone;
    case Parity::PARITY_INVALID:
        return comInvalidParameter;
    }

    return comInvalidParameter;
}

Parity SerialCom::uintToParity(const unsigned int parity)
{
    switch (parity)
    {
    case comParityEven:
        return Parity::PARITY_EVEN;
    case comParityOdd:
        return Parity::PARITY_ODD;
    case comParityNone:
        return Parity::PARITY_NONE;
    }

    return Parity::PARITY_INVALID;
}

unsigned int SerialCom::stopBitsToUint(const StopBits stop)
{
    switch (stop)
    {
    case StopBits::STOP_BITS_1:
        return comStopBits1;
    case StopBits::STOP_BITS_2:
        return comStopBits2;
    case StopBits::STOP_BITS_INVALID:
        return comInvalidParameter;
    }

    return comInvalidParameter;
}

StopBits SerialCom::uintToStopBits(const unsigned int stop)
{
    switch (stop)
    {
    case comStopBits1:
        return StopBits::STOP_BITS_1;
    case comStopBits2:
        return StopBits::STOP_BITS_2;
    }

    return StopBits::STOP_BITS_INVALID;
}

