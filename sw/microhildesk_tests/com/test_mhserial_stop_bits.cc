#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert stop-bits to uint
/// @param MHSerialComTest is test fixture
/// @param StopBitsToUIntTest is test name
TEST_F(MHSerialComTest, StopBitsToUIntTest)
{
    const StopBits stop_bits = StopBits::STOP_BITS_1;
    unsigned int converted = m_serial.stopBitsToUInt(stop_bits);
    unsigned int stop_bits_expected = 0;

    EXPECT_TRUE(stop_bits_expected == converted);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert uint to stop-bits
/// @param MHSerialComTest is test fixture
/// @param UIntToStopBitsTest is test name
TEST_F(MHSerialComTest, UIntToStopBitsTest)
{
    const unsigned int stop_bits = 0;
    const StopBits stop_bits_expected = StopBits::STOP_BITS_1;
    StopBits converted = m_serial.uintToStopBits(stop_bits);

    EXPECT_TRUE(stop_bits_expected == converted);
}
