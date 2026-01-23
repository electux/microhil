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
    //////////////////////////////////////////////////////////////////////////
    /// @brief Serial communication parameters
    constexpr const unsigned int comParamBaudIndex{0};
    constexpr const unsigned int comParamDataIndex{1};
    constexpr const unsigned int comParamParityIndex{2};
    constexpr const unsigned int comParamStopIndex{3};
    constexpr const unsigned int comParamFlowControlIndex{4};
    constexpr std::string_view comBaudRates[]{
        "110", "300", "600", "1200", "2400", "4800", "9600",
        "19200", "38400", "57600", "115200", "230400"
    };
    constexpr std::string_view comDataBits[]{"5", "6", "7", "8"};
    constexpr std::string_view comParities[]{"Even", "Odd", "None"};
    constexpr std::string_view comStopBits[]{"1", "2"};
    constexpr std::string_view comFlowControls[]{"None", "Hardware", "Software"};
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
    constexpr const unsigned int comFlowControlNone = 0;
    constexpr const unsigned int comFlowControlHw = 1;
    constexpr const unsigned int comFlowControlSw = 2;
    constexpr const unsigned int comInvalidParameter = 127;
};
