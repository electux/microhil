#include "test_mhlog.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test write log message
/// @param MHConfigTest is test fixture
/// @param WriteTest is test name
TEST_F(MHLogTest, WriteTest)
{
    log.setFilePath("test.log");
    log.setLogLevel(LogLevel::MICROHIL_INFO);
    log.open();

    EXPECT_NO_THROW(log.write("test", LogLevel::MICROHIL_INFO));
}
