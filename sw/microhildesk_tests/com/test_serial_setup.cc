/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_setup.cc
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
#include "test_serial_com.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test the setup serial port
/// @param SerialComTest is test fixture
/// @param setupSerialPortTest is test name
TEST_F(SerialComTest, setupSerialPortTest)
{
    const std::string device = "/dev/ttyUSB0";
    const SerialParams params = {
        .device = device,
        .baud = BaudRate::BAUD_115200,
        .data = CharacterSize::CHAR_SIZE_8,
        .parity = Parity::PARITY_NONE,
        .stop = StopBits::STOP_BITS_1,
        .flow = FlowControl::FLOW_CONTROL_NONE
    };

    EXPECT_NO_THROW(m_serial.setup(params));
}
