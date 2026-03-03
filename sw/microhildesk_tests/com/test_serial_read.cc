////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_read.cc
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
/// @brief Test reading from the serial port using a pseudo-terminal.
///
/// This test simulates incoming data by writing to the master end of a pseudo-terminal
/// and verifies that the SerialCom instance can read it correctly from the slave end.
///
/// @param SerialComTest The test fixture.
/// @param ReadFromPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, ReadFromPortTest)
{
    m_serial.open();
    std::string mock_response = "ACK\n";
	std::vector<uint8_t> result;

    write(master_fd, mock_response.c_str(), mock_response.length());
    m_serial.read(result, mock_response.length());

    EXPECT_EQ(result.size(), mock_response.length());
    EXPECT_EQ(std::string(result.begin(), result.end()), mock_response);
}
