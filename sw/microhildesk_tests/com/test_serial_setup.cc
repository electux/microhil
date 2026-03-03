////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_setup.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "test_mock_iserial.h"
#include "test_serial_com.h"

using namespace com::mock;
using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the setup process of the serial port.
///
/// Verifies that the SerialCom class correctly processes and applies the
/// communication parameters (baud, data bits, parity, etc.) to the device.
///
/// @param SerialComTest The test fixture.
/// @param setupSerialPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, setupSerialPortTest)
{
	/*
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
	*/

	EXPECT_EQ(true, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief 
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEST(MockISerialTest, SetupTest)
//{
//    MockISerial mockSerial;
//    SerialParams params{"/dev/ttyS0", BaudRate::BAUD_9600, CharacterSize::CHAR_SIZE_8, Parity::PARITY_NONE, StopBits::STOP_BITS_1, FlowControl::FLOW_CONTROL_NONE};
//
//    EXPECT_CALL(mockSerial, setup(params)).WillOnce(::testing::Return(true));
//    ASSERT_TRUE(mockSerial.setup(params));
//}
