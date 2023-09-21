#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set stop-bits
/// @param MHConfigTest is test fixture
/// @param SetStopBitsTest is test name
TEST_F(MHConfigTest, SetStopBitsTest)
{
    int stop_bits = 1;

    EXPECT_NO_THROW(m_config.setDataBits(stop_bits));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get stop-bits
/// @param MHConfigTest is test fixture
/// @param GetStopBitsTest is test name
TEST_F(MHConfigTest, GetStopBitsTest)
{
    int stop_bits = 1;
    int expected = 1;
    m_config.setDataBits(stop_bits);

    EXPECT_TRUE(m_config.getDataBits() == expected);
}
