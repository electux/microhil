#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert parity to uint
/// @param MHSerialComTest is test fixture
/// @param ParityToUIntTest is test name
TEST_F(MHSerialComTest, ParityToUIntTest)
{
    const Parity parity = Parity::PARITY_NONE;
    unsigned int converted = m_serial.parityToUInt(parity);
    unsigned int parity_expected = 2;

    EXPECT_TRUE(parity_expected == converted);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert uint to parity
/// @param MHSerialComTest is test fixture
/// @param UIntToParityTest is test name
TEST_F(MHSerialComTest, UIntToParityTest)
{
    const unsigned int parity = 2;
    const Parity parity_expected = Parity::PARITY_NONE;
    Parity converted = m_serial.uintToParity(parity);

    EXPECT_TRUE(parity_expected == converted);
}
