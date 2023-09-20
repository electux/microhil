#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set baud rate function
/// @param MHConfigTest is test fixture
/// @param SetBaudRateTest is test name
TEST_F(MHConfigTest, SetBaudRateTest)
{
    int baud_115200 = 115200;

    EXPECT_NO_THROW(m_config.setBaudRate(baud_115200));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test the valid function
/// @param MHConfigTest is test fixture
/// @param GetBaudRateTest is test name
TEST_F(MHConfigTest, GetBaudRateTest)
{
    int baud_115200_index = 11;
    int baud_115200 = 115200;

    m_config.setBaudRate(baud_115200);
    int baud_rate_index_to_check = m_config.getBaudRate();

    ASSERT_TRUE(baud_115200_index == baud_rate_index_to_check);
}
