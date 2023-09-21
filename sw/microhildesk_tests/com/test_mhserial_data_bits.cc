#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test data-bits to uint
/// @param MHSerialComTest is test fixture
/// @param DataBitsToUIntTest is test name
TEST_F(MHSerialComTest, DataBitsToUIntTest)
{
    const CharacterSize data_bits = CharacterSize::CHAR_SIZE_8;
    unsigned int data_bits_to_check = m_serial.dataBitsToUInt(data_bits);
    unsigned int data_bits_expected = 48;

    EXPECT_TRUE(data_bits_to_check == data_bits_expected);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test uint to data-bits
/// @param MHSerialComTest is test fixture
/// @param UIntToDataBitsTest is test name
TEST_F(MHSerialComTest, UIntToDataBitsTest)
{
    unsigned int data_bits = 48;
    const CharacterSize data_bits_to_check = m_serial.uintToDataBits(data_bits);
    CharacterSize data_bits_expected = CharacterSize::CHAR_SIZE_8;

    EXPECT_TRUE(data_bits_to_check == data_bits_expected);
}
