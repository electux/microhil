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
    constexpr const unsigned int com_baud_110 = 0;
    constexpr const unsigned int com_baud_300 = 1;
    constexpr const unsigned int com_baud_600 = 2;
    constexpr const unsigned int com_baud_1200 = 3;
    constexpr const unsigned int com_baud_2400 = 4;
    constexpr const unsigned int com_baud_4800 = 5;
    constexpr const unsigned int com_baud_9600 = 6;
    constexpr const unsigned int com_baud_19200 = 7;
    constexpr const unsigned int com_baud_38400 = 8;
    constexpr const unsigned int com_baud_57600 = 9;
    constexpr const unsigned int com_baud_115200 = 10;
    constexpr const unsigned int com_baud_230400 = 11;
    constexpr const unsigned int com_data_bits_5 = 0;
    constexpr const unsigned int com_data_bits_6 = 1;
    constexpr const unsigned int com_data_bits_7 = 2;
    constexpr const unsigned int com_data_bits_8 = 3; 
    constexpr const unsigned int com_parity_even = 0;
    constexpr const unsigned int com_parity_odd = 1;
    constexpr const unsigned int com_parity_none = 2;
    constexpr const unsigned int com_stop_bits_1 = 0;
    constexpr const unsigned int com_stop_bits_2 = 1;
    constexpr const unsigned int com_invalid_parameter = 127;
};

using namespace Electux::App::Com;

unsigned int SerialCom::baud_to_uint(const BaudRate baud)
{
    switch (baud)
    {
    case BaudRate::BAUD_50:
        return com_invalid_parameter;
    case BaudRate::BAUD_75:
        return com_invalid_parameter;
    case BaudRate::BAUD_110:
        return com_baud_110;
    case BaudRate::BAUD_134:
        return com_invalid_parameter;
    case BaudRate::BAUD_150:
        return com_invalid_parameter;
    case BaudRate::BAUD_200:
        return com_invalid_parameter;
    case BaudRate::BAUD_300:
        return com_baud_300;
    case BaudRate::BAUD_600:
        return com_baud_600;
    case BaudRate::BAUD_1200:
        return com_baud_1200;
    case BaudRate::BAUD_1800:
        return com_invalid_parameter;
    case BaudRate::BAUD_2400:
        return com_baud_2400;
    case BaudRate::BAUD_4800:
        return com_baud_4800;
    case BaudRate::BAUD_9600:
        return com_baud_9600;
    case BaudRate::BAUD_19200:
        return com_baud_19200;
    case BaudRate::BAUD_38400:
        return com_baud_38400;
    case BaudRate::BAUD_57600:
        return com_baud_57600;
    case BaudRate::BAUD_115200:
        return com_baud_115200;
    case BaudRate::BAUD_230400:
        return com_baud_230400;
    case BaudRate::BAUD_460800:
        return com_invalid_parameter;
    case BaudRate::BAUD_500000:
        return com_invalid_parameter;
    case BaudRate::BAUD_576000:
        return com_invalid_parameter;
    case BaudRate::BAUD_921600:
        return com_invalid_parameter;
    case BaudRate::BAUD_1000000:
        return com_invalid_parameter;
    case BaudRate::BAUD_1152000:
        return com_invalid_parameter;
    case BaudRate::BAUD_1500000:
        return com_invalid_parameter;
    case BaudRate::BAUD_2000000:
        return com_invalid_parameter;
    case BaudRate::BAUD_2500000:
        return com_invalid_parameter;
    case BaudRate::BAUD_3000000:
        return com_invalid_parameter;
    case BaudRate::BAUD_3500000:
        return com_invalid_parameter;
    case BaudRate::BAUD_4000000:
        return com_invalid_parameter;
    case BaudRate::BAUD_INVALID:
        return com_invalid_parameter;
    }

    return com_invalid_parameter;
}

BaudRate SerialCom::uint_to_baud(const unsigned int baud)
{
    switch (baud)
    {
    case com_baud_110:
        return BaudRate::BAUD_110;
    case com_baud_300:
        return BaudRate::BAUD_300;
    case com_baud_600:
        return BaudRate::BAUD_600;
    case com_baud_1200:
        return BaudRate::BAUD_1200;
    case com_baud_2400:
        return BaudRate::BAUD_2400;
    case com_baud_4800:
        return BaudRate::BAUD_4800;
    case com_baud_9600:
        return BaudRate::BAUD_9600;
    case com_baud_19200:
        return BaudRate::BAUD_19200;
    case com_baud_38400:
        return BaudRate::BAUD_38400;
    case com_baud_57600:
        return BaudRate::BAUD_57600;
    case com_baud_115200:
        return BaudRate::BAUD_115200;
    case com_baud_230400:
        return BaudRate::BAUD_230400;
    }

    return BaudRate::BAUD_INVALID;
}

unsigned int SerialCom::data_bits_to_uint(const CharacterSize data)
{
    switch (data)
    {
    case CharacterSize::CHAR_SIZE_5:
        return com_data_bits_5;
    case CharacterSize::CHAR_SIZE_6:
        return com_data_bits_6;
    case CharacterSize::CHAR_SIZE_7:
        return com_data_bits_7;
    case CharacterSize::CHAR_SIZE_8:
        return com_data_bits_8;
    case CharacterSize::CHAR_SIZE_INVALID:
        return com_invalid_parameter;
    }

    return com_invalid_parameter;
}

CharacterSize SerialCom::uint_to_data_bits(const unsigned int data)
{
    switch (data)
    {
    case com_data_bits_5:
        return CharacterSize::CHAR_SIZE_5;
    case com_data_bits_6:
        return CharacterSize::CHAR_SIZE_6;
    case com_data_bits_7:
        return CharacterSize::CHAR_SIZE_7;
    case com_data_bits_8:
        return CharacterSize::CHAR_SIZE_8;
    }

    return CharacterSize::CHAR_SIZE_INVALID;
}

unsigned int SerialCom::parity_to_uint(const Parity parity)
{
    switch (parity)
    {
    case Parity::PARITY_EVEN:
        return com_parity_even;
    case Parity::PARITY_ODD:
        return com_parity_odd;
    case Parity::PARITY_NONE:
        return com_parity_none;
    case Parity::PARITY_INVALID:
        return com_invalid_parameter;
    }

    return com_invalid_parameter;
}

Parity SerialCom::uint_to_parity(const unsigned int parity)
{
    switch (parity)
    {
    case com_parity_even:
        return Parity::PARITY_EVEN;
    case com_parity_odd:
        return Parity::PARITY_ODD;
    case com_parity_none:
        return Parity::PARITY_NONE;
    }

    return Parity::PARITY_INVALID;
}

unsigned int SerialCom::stop_bits_to_uint(const StopBits stop)
{
    switch (stop)
    {
    case StopBits::STOP_BITS_1:
        return com_stop_bits_1;
    case StopBits::STOP_BITS_2:
        return com_stop_bits_2;
    case StopBits::STOP_BITS_INVALID:
        return com_invalid_parameter;
    }

    return com_invalid_parameter;
}

StopBits SerialCom::uint_to_stop_bits(const unsigned int stop)
{
    switch (stop)
    {
    case com_stop_bits_1:
        return StopBits::STOP_BITS_1;
    case com_stop_bits_2:
        return StopBits::STOP_BITS_2;
    }

    return StopBits::STOP_BITS_INVALID;
}

