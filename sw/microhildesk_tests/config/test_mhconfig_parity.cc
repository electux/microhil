#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set parity
/// @param MHConfigTest is test fixture
/// @param SetParityTest is test name
TEST_F(MHConfigTest, SetParityTest)
{
    int parity = 0;

    EXPECT_NO_THROW(m_config.setParity(parity));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get parity
/// @param MHConfigTest is test fixture
/// @param GetParityTest is test name
TEST_F(MHConfigTest, GetParityTest)
{
    int parity = 0;
    MHString expected = "None";
    m_config.setParity(parity);

    EXPECT_TRUE(m_config.getParity() == expected);
}
