#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set log level
/// @param MHConfigTest is test fixture
/// @param SetLogLevelTest is test name
TEST_F(MHConfigTest, SetLogLevelTest)
{
    int log_level = 0;

    EXPECT_NO_THROW(m_config.setLogLevel(log_level));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get log level
/// @param MHConfigTest is test fixture
/// @param GetLogLevelTest is test name
TEST_F(MHConfigTest, GetLogLevelTest)
{
    int log_level = 0;
    MHString expected = "INFO";
    m_config.setLogLevel(log_level);

    EXPECT_TRUE(m_config.getLogLevel() == expected);
}
