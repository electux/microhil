/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com_params.h
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
#pragma once

#include <string_view>

namespace Electux::App::Params::SerialComConstants {
    ///////////////////////////////////////////////////////////////////////////
    /// @brief Serial communication parameters
    ///   cComBaudRates - Supported Baud Rates
    ///   cComDataBits - Supported Data Bits
    ///   cComParities - Supported Parities
    ///   cComStopBits - Supported Stop Bits
    ///   cComFlowControls - Supported Flow Controls
    ///   cComBaudXXX - Constant index for each Baud Rate
    ///   cComDataBitsX - Constant index for each Data Bits option
    ///   cComParityX - Constant index for each Parity option
    ///   cComStopBitsX - Constant index for each Stop Bits option
    ///   cComFlowControlX - Constant index for each Flow Control option
    ///   cComInvalidParameter - Constant for invalid parameter
    constexpr std::string_view cComBaudRates[]{
        "110", "300", "600", "1200", "2400", "4800", "9600",
        "19200", "38400", "57600", "115200", "230400"
    };
    constexpr std::string_view cComDataBits[]{"5", "6", "7", "8"};
    constexpr std::string_view cComParities[]{"Even", "Odd", "None"};
    constexpr std::string_view cComStopBits[]{"1", "2"};
    constexpr std::string_view cComFlowControls[]{"None", "Hardware", "Software"};
    constexpr const uint32_t cComBaud110 = 0;
    constexpr const uint32_t cComBaud300 = 1;
    constexpr const uint32_t cComBaud600 = 2;
    constexpr const uint32_t cComBaud1200 = 3;
    constexpr const uint32_t cComBaud2400 = 4;
    constexpr const uint32_t cComBaud4800 = 5;
    constexpr const uint32_t cComBaud9600 = 6;
    constexpr const uint32_t cComBaud19200 = 7;
    constexpr const uint32_t cComBaud38400 = 8;
    constexpr const uint32_t cComBaud57600 = 9;
    constexpr const uint32_t cComBaud115200 = 10;
    constexpr const uint32_t cComBaud230400 = 11;
    constexpr const uint32_t cComDataBits5 = 0;
    constexpr const uint32_t cComDataBits6 = 1;
    constexpr const uint32_t cComDataBits7 = 2;
    constexpr const uint32_t cComDataBits8 = 3;
    constexpr const uint32_t cComParityEven = 0;
    constexpr const uint32_t cComParityOdd = 1;
    constexpr const uint32_t cComParityNone = 2;
    constexpr const uint32_t cComStopBits1 = 0;
    constexpr const uint32_t cComStopBits2 = 1;
    constexpr const uint32_t cComFlowControlNone = 0;
    constexpr const uint32_t cComFlowControlHw = 1;
    constexpr const uint32_t cComFlowControlSw = 2;
    constexpr const uint32_t cComInvalidParameter = 127;
};
