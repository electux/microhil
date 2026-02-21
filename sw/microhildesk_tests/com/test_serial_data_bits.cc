/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_data_bits.cc
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
/// @brief Test conversion data-bits to uint32_t
/// @param SerialComTest is test fixture
/// @param DataBitsToUintTest is test name
TEST_F(SerialComTest, dataBitsToUintTest)
{
    const CharacterSize data_bits = CharacterSize::CHAR_SIZE_8;
    const uint32_t data_bits_to_check = m_serial.dataBitsToUint(data_bits);
    const uint32_t data_bits_expected = 48;

    EXPECT_TRUE(data_bits_to_check == data_bits_expected);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion uint32_t to data-bits
/// @param SerialComTest is test fixture
/// @param uintToDataBitsTest is test name
TEST_F(SerialComTest, uintToDataBitsTest)
{
    const uint32_t data_bits = 48;
    const CharacterSize data_bits_to_check = m_serial.uintToDataBits(data_bits);
    const CharacterSize data_bits_expected = CharacterSize::CHAR_SIZE_8;

    EXPECT_TRUE(data_bits_to_check == data_bits_expected);
}
