////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_write.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "test_serial_com.h"

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test writing to the serial port using a pseudo-terminal.
///
/// This test simulates incoming data by writing to the master end of a pseudo-terminal
/// and verifies that the SerialCom instance can read it correctly from the slave end.
///
/// @param SerialComTest The test fixture.
/// @param WriteToPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, WriteToPortTest)
{
    m_serial.open();
    const std::vector<uint8_t> test_data = {'H','E','L','L','O','_','P','T','Y'};
    m_serial.write(test_data);
    char buffer[64] = {0};
    int n = read(master_fd, buffer, sizeof(buffer));

    EXPECT_EQ(std::vector<uint8_t>(buffer, buffer + n), test_data);
}
