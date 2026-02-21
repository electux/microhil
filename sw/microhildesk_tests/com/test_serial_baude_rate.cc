/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_baude_rate.cc
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

///////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion baud-rate to uint32_t
/// @param SerialComTest is test fixture
/// @param baudToUintTest is test name
TEST_F(SerialComTest, baudToUintTest)
{
    const BaudRate baud_rate = BaudRate::BAUD_115200;
    const uint32_t converted = m_serial.baudToUint(baud_rate);
    const uint32_t baud_expected = 4098;

    EXPECT_TRUE(baud_expected == converted);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion uint32_t to baud-rate
/// @param SerialComTest is test fixture
/// @param uintToBaudTest is test name
TEST_F(SerialComTest, uintToBaudTest)
{
    const uint32_t baud_rate = 4098;
    const BaudRate baud_expected = BaudRate::BAUD_115200;
    BaudRate converted = m_serial.uintToBaud(baud_rate);

    EXPECT_TRUE(baud_expected == converted);
}
