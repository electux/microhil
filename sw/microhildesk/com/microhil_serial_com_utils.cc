/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_serial_com.cc
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
#include "microhil_serial_com.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief baud-rate index values
    constexpr const unsigned int kBaud110 = 0;
    constexpr const unsigned int kBaud300 = 1;
    constexpr const unsigned int kBaud600 = 2;
    constexpr const unsigned int kBaud1200 = 3;
    constexpr const unsigned int kBaud2400 = 4;
    constexpr const unsigned int kBaud4800 = 5;
    constexpr const unsigned int kBaud9600 = 6;
    constexpr const unsigned int kBaud19200 = 7;
    constexpr const unsigned int kBaud38400 = 8;
    constexpr const unsigned int kBaud57600 = 9;
    constexpr const unsigned int kBaud115200 = 10;
    constexpr const unsigned int kBaud230400 = 11;

    ////////////////////////////////////////////////////////////////////////
    /// @brief data-bits index values
    constexpr const unsigned int kDataBits5 = 0;
    constexpr const unsigned int kDataBits6 = 1;
    constexpr const unsigned int kDataBits7 = 2;
    constexpr const unsigned int kDataBits8 = 3;

    ////////////////////////////////////////////////////////////////////////
    /// @brief parity index values
    constexpr const unsigned int kParityEven = 0;
    constexpr const unsigned int kParityOdd = 1;
    constexpr const unsigned int kParityNone = 2;

    ////////////////////////////////////////////////////////////////////////
    /// @brief stop-bits index values
    constexpr const unsigned int kStopBits1 = 0;
    constexpr const unsigned int kStopBits2 = 1;

    ////////////////////////////////////////////////////////////////////////
    /// @brief invalid parameter for serial port
    constexpr const unsigned int kInvalidParameter = 127;
}

unsigned int MicroHILSerialCom::baudRateToUInt(const BaudRate baudRate)
{
    switch(baudRate)
    {
        case BaudRate::BAUD_50: return kInvalidParameter;
        case BaudRate::BAUD_75: return kInvalidParameter;
        case BaudRate::BAUD_110: return kBaud110;
        case BaudRate::BAUD_134: return kInvalidParameter;
        case BaudRate::BAUD_150: return kInvalidParameter;
        case BaudRate::BAUD_200: return kInvalidParameter;
        case BaudRate::BAUD_300: return kBaud300;
        case BaudRate::BAUD_600: return kBaud600;
        case BaudRate::BAUD_1200: return kBaud1200;
        case BaudRate::BAUD_1800: return kInvalidParameter;
        case BaudRate::BAUD_2400: return kBaud2400;
        case BaudRate::BAUD_4800: return kBaud4800;
        case BaudRate::BAUD_9600: return kBaud9600;
        case BaudRate::BAUD_19200: return kBaud19200;
        case BaudRate::BAUD_38400: return kBaud38400;
        case BaudRate::BAUD_57600: return kBaud57600;
        case BaudRate::BAUD_115200: return kBaud115200;
        case BaudRate::BAUD_230400: return kBaud230400;
        case BaudRate::BAUD_460800: return kInvalidParameter;
        case BaudRate::BAUD_500000: return kInvalidParameter;
        case BaudRate::BAUD_576000: return kInvalidParameter;
        case BaudRate::BAUD_921600: return kInvalidParameter;
        case BaudRate::BAUD_1000000: return kInvalidParameter;
        case BaudRate::BAUD_1152000: return kInvalidParameter;
        case BaudRate::BAUD_1500000: return kInvalidParameter;
        case BaudRate::BAUD_2000000: return kInvalidParameter;
        case BaudRate::BAUD_2500000: return kInvalidParameter;
        case BaudRate::BAUD_3000000: return kInvalidParameter;
        case BaudRate::BAUD_3500000: return kInvalidParameter;
        case BaudRate::BAUD_4000000: return kInvalidParameter;
        case BaudRate::BAUD_INVALID: return kInvalidParameter;
    }

    return kInvalidParameter;
}

BaudRate MicroHILSerialCom::uintToBaudRate(const unsigned int baudRate)
{
    switch(baudRate)
    {
        case kBaud110: return BaudRate::BAUD_110;
        case kBaud300: return BaudRate::BAUD_300;
        case kBaud600: return BaudRate::BAUD_600;
        case kBaud1200: return BaudRate::BAUD_1200;
        case kBaud2400: return BaudRate::BAUD_2400;
        case kBaud4800: return BaudRate::BAUD_4800;
        case kBaud9600: return BaudRate::BAUD_9600;
        case kBaud19200: return BaudRate::BAUD_19200;
        case kBaud38400: return BaudRate::BAUD_38400;
        case kBaud57600: return BaudRate::BAUD_57600;
        case kBaud115200: return BaudRate::BAUD_115200;
        case kBaud230400: return BaudRate::BAUD_230400;
    }

    return BaudRate::BAUD_INVALID;
}

unsigned int MicroHILSerialCom::dataBitsToUInt(const CharacterSize dataBits)
{
    switch(dataBits)
    {
        case CharacterSize::CHAR_SIZE_5: return kDataBits5;
        case CharacterSize::CHAR_SIZE_6: return kDataBits6;
        case CharacterSize::CHAR_SIZE_7: return kDataBits7;
        case CharacterSize::CHAR_SIZE_8: return kDataBits8;
        case CharacterSize::CHAR_SIZE_INVALID: return kInvalidParameter;
    }

    return kInvalidParameter;
}

CharacterSize MicroHILSerialCom::uintToDataBits(const unsigned int dataBits)
{
    switch(dataBits)
    {
        case kDataBits5: return CharacterSize::CHAR_SIZE_5;
        case kDataBits6: return CharacterSize::CHAR_SIZE_6;
        case kDataBits7: return CharacterSize::CHAR_SIZE_7;
        case kDataBits8: return CharacterSize::CHAR_SIZE_8;
    }

    return CharacterSize::CHAR_SIZE_INVALID;
}

unsigned int MicroHILSerialCom::parityToUInt(const Parity parity)
{
    switch(parity)
    {
        case Parity::PARITY_EVEN: return kParityEven;
        case Parity::PARITY_ODD: return kParityOdd;
        case Parity::PARITY_NONE: return kParityNone;
        case Parity::PARITY_INVALID: return kInvalidParameter; 
    }

    return kInvalidParameter;
}

Parity MicroHILSerialCom::uintToParity(const unsigned int parity)
{
    switch(parity)
    {
        case kParityEven: return Parity::PARITY_EVEN;
        case kParityOdd: return Parity::PARITY_ODD;
        case kParityNone: return Parity::PARITY_NONE;
    }

    return Parity::PARITY_INVALID;
}

unsigned int MicroHILSerialCom::stopBitsToUInt(const StopBits stopBits)
{
    switch(stopBits)
    {
        case StopBits::STOP_BITS_1: return kStopBits1;
        case StopBits::STOP_BITS_2: return kStopBits2;
        case StopBits::STOP_BITS_INVALID: return kInvalidParameter;
    }

    return kInvalidParameter;
}

StopBits MicroHILSerialCom::uintToStopBits(const unsigned int stopBits)
{
    switch(stopBits)
    {
        case kStopBits1: return StopBits::STOP_BITS_1;
        case kStopBits2: return StopBits::STOP_BITS_2;
    }

    return StopBits::STOP_BITS_INVALID;
}
