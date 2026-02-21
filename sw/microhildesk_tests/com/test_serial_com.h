/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_com.h
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

#include <gtest/gtest.h>
#include <com/serial_com.h>

namespace Electux::App::Com
{
    ///////////////////////////////////////////////////////////////////////////
    /// @brief Proxy class to expose protected SerialCom methods for testing
    class SerialComProxy : public SerialCom
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Promoting protected methods to public for unit testing
        using SerialCom::baudToUint;
        using SerialCom::uintToBaud;
        using SerialCom::dataBitsToUint;
        using SerialCom::uintToDataBits;
        using SerialCom::parityToUint;
        using SerialCom::uintToParity;
        using SerialCom::stopBitsToUint;
        using SerialCom::uintToStopBits;
        using SerialCom::flowControlToUint;
        using SerialCom::uintToFlowControl;
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Test fixture for SerialCom class
    class SerialComTest : public ::testing::Test
    {
    protected:
        ///////////////////////////////////////////////////////////////////////////
        /// @brief Local aliases to keep the test code clean
        using SerialCom = Electux::App::Com::SerialComProxy;
        using BaudRate = Electux::App::Com::BaudRate;
        using CharacterSize = Electux::App::Com::CharacterSize;
        using Parity = Electux::App::Com::Parity;
        using StopBits = Electux::App::Com::StopBits;
        using FlowControl = Electux::App::Com::FlowControl;
        using SerialParams = Electux::App::Com::SerialParams;

        ///////////////////////////////////////////////////////////////////////////
        /// @brief The instance being tested is now the Proxy
        SerialCom m_serial{};

        void SetUp() override
        {
            // Initialization if necessary
        }

        void TearDown() override
        {
            // Cleanup if necessary
        }
    };
}
