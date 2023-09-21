#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test the valid function
/// @param MHConfigTest is test fixture
/// @param GetDataBitsTest is test name
TEST_F(MHConfigTest, GetDataBitsTest)
{
    const int data_bits = 48;
    m_config.setDataBits(data_bits);

    EXPECT_NO_THROW(m_config.getDataBits());
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test set data-bits
/// @param MHConfigTest is test fixture
/// @param SetDataBitsTest is test name
TEST_F(MHConfigTest, SetDataBitsTest)
{
    const int data_bits = 48;
    m_config.setDataBits(data_bits);

    EXPECT_TRUE(m_config.getDataBits() == data_bits);
}
