/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_stop_bits.cc
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

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion stop-bits to uint32_t
/// @param SerialComTest is test fixture
/// @param stopBitsToUintTest is test name
TEST_F(SerialComTest, stopBitsToUintTest)
{
    const StopBits stop_bits = StopBits::STOP_BITS_1;
    const uint32_t converted = m_serial.stopBitsToUint(stop_bits);
    const uint32_t stop_bits_expected = 0;

    EXPECT_TRUE(stop_bits_expected == converted);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion uint32_t to stop-bits
/// @param SerialComTest is test fixture
/// @param uintToStopBitsTest is test name
TEST_F(SerialComTest, uintToStopBitsTest)
{
    const uint32_t stop_bits = 0;
    const StopBits stop_bits_expected = StopBits::STOP_BITS_1;
    StopBits converted = m_serial.uintToStopBits(stop_bits);

    EXPECT_TRUE(stop_bits_expected == converted);
}
