#include "test_mhlog.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test close log file
/// @param MHConfigTest is test fixture
/// @param CloseTest is test name
TEST_F(MHLogTest, CloseTest)
{
    log.setFilePath("test.log");
    log.setLogLevel(LogLevel::MICROHIL_INFO);
    auto status = log.open();

    EXPECT_TRUE(log.close() == true);
}
