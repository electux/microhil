#include "test_mhlog.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test open log file
/// @param MHConfigTest is test fixture
/// @param OpenTest is test name
TEST_F(MHLogTest, OpenTest)
{
    log.setFilePath("test.log");
    log.setLogLevel(LogLevel::MICROHIL_INFO);

    EXPECT_TRUE(log.open() == true);
}
