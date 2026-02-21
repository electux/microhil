/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_serial_parity.cc
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
/// @brief Test conversion parity to uint32_t
/// @param SerialComTest is test fixture
/// @param parityToUintTest is test name
TEST_F(SerialComTest, parityToUintTest)
{
    const Parity parity = Parity::PARITY_NONE;
    const uint32_t converted = m_serial.parityToUint(parity);
    const uint32_t parity_expected = 2;

    EXPECT_TRUE(parity_expected == converted);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test conversion uint32_t to parity
/// @param SerialComTest is test fixture
/// @param uintToParityTest is test name
TEST_F(SerialComTest, uintToParityTest)
{
    const uint32_t parity = 2;
    const Parity parity_expected = Parity::PARITY_NONE;
    Parity converted = m_serial.uintToParity(parity);

    EXPECT_TRUE(parity_expected == converted);
}
