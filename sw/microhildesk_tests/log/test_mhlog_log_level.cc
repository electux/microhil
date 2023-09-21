#include "test_mhlog.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set log level
/// @param MHConfigTest is test fixture
/// @param SetLogLevelTest is test name
TEST_F(MHLogTest, SetLogLevelTest)
{
    const LogLevel level = LogLevel::MICROHIL_INFO;

    EXPECT_NO_THROW(log.setLogLevel(level));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get log level
/// @param MHConfigTest is test fixture
/// @param GetLogLevelTest is test name
TEST_F(MHLogTest, GetLogLevelTest)
{
    const LogLevel level = LogLevel::MICROHIL_INFO;
    log.setLogLevel(level);

    EXPECT_EQ(log.getLogLevel(), level);
}
