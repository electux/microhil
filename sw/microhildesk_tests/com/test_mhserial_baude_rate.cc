#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert baud-rate to uint
/// @param MHSerialComTest is test fixture
/// @param BaudRateToUIntTest is test name
TEST_F(MHSerialComTest, BaudRateToUIntTest)
{
    const BaudRate baud_rate = BaudRate::BAUD_115200;
    unsigned int converted = m_serial.baudRateToUInt(baud_rate);
    unsigned int baud_expected = 4098;

    EXPECT_TRUE(baud_expected == converted);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert uint to baud-rate
/// @param MHSerialComTest is test fixture
/// @param BaudRateToUIntTest is test name
TEST_F(MHSerialComTest, UIntToBaudRateTest)
{
    const unsigned int baud_rate = 4098;
    const BaudRate baud_expected = BaudRate::BAUD_115200;
    BaudRate converted = m_serial.uintToBaudRate(baud_rate);

    EXPECT_TRUE(baud_expected == converted);
}
