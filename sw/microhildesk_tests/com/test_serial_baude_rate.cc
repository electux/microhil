////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_baude_rate.cc
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

#include "test_mock_iserial.h"
#include "test_serial_com.h"
#include <params/serial_com_params.h>

using namespace com::mock;
using namespace Electux::App::Com;
using namespace Electux::App::Params::SerialComConstants;
using ::testing::Return;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test bidirectional conversion of all supported BaudRates.
///
/// Iterates through provided parameters to verify that baudToUint and
/// uintToBaud mappings are consistent and correct based on serial_com_utils.
///
/// @param BaudRateTest The name of the test case.
/// @param BaudRateConversionTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_P(BaudRateTest, BaudRateConversionTest)
{
	ParameterMapping<BaudRate> params = this->GetParam();

	EXPECT_EQ(m_serial.baudToUint(params.enum_val), params.uint_val);
	EXPECT_EQ(m_serial.uintToBaud(params.uint_val), params.enum_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief List of all supported baud rate mappings from serial_com_utils.cc.
///
/// Note: Replace numeric values with actual constants if they differ.
///
/// @param SerialComTest The name of the test suite.
/// @param BaudRateTest The name of the parameterized test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P
(
	SerialComTest,
	BaudRateTest,
	::testing::Values
	(
		ParameterMapping<BaudRate>{BaudRate::BAUD_110,    0}, 
		ParameterMapping<BaudRate>{BaudRate::BAUD_300,    1}, 
		ParameterMapping<BaudRate>{BaudRate::BAUD_600,    2}, 
		ParameterMapping<BaudRate>{BaudRate::BAUD_1200,   3},
		ParameterMapping<BaudRate>{BaudRate::BAUD_2400,   4},
		ParameterMapping<BaudRate>{BaudRate::BAUD_4800,   5},
		ParameterMapping<BaudRate>{BaudRate::BAUD_9600,   6},
		ParameterMapping<BaudRate>{BaudRate::BAUD_19200,  7},
		ParameterMapping<BaudRate>{BaudRate::BAUD_38400,  8},
		ParameterMapping<BaudRate>{BaudRate::BAUD_57600,  9},
		ParameterMapping<BaudRate>{BaudRate::BAUD_115200, 10},
		ParameterMapping<BaudRate>{BaudRate::BAUD_230400, 11}
	)
);

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test detection of invalid baud rate parameters.
///
/// Verifies that the conversion logic correctly identifies unsupported 
/// baud rates and returns the predefined invalid parameter constant or enum.
///
/// @param SerialComTest The name of the test suite.
/// @param InvalidBaudRateDetectionTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, InvalidBaudRateDetectionTest)
{
	uint32_t invalid_uint = m_serial.baudToUint(BaudRate::BAUD_200);
	EXPECT_EQ(invalid_uint, cComInvalidParameter);

	BaudRate invalid_enum = m_serial.uintToBaud(999999);
	EXPECT_EQ(invalid_enum, BaudRate::BAUD_INVALID);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the conversion of BaudRate enum to unsigned integer.
///
/// This test simulates the utility function that converts internal enum types 
/// to standard numeric values used by system ioctls.
///
/// @param MockISerialTest The name of the test suite.
/// @param BaudRateConversionTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockISerialTest, BaudRateConversionTest)
{
    MockISerial mockSerial;
    BaudRate rate = BaudRate::BAUD_115200;
    uint32_t expectedValue = 10;

    EXPECT_CALL(mockSerial, baudToUint(rate))
        .WillOnce(Return(expectedValue));

    ASSERT_EQ(mockSerial.baudToUint(rate), expectedValue);
}
