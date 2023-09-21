#include "test_mhlog.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set file path
/// @param MHConfigTest is test fixture
/// @param SetFilePathTest is test name
TEST_F(MHLogTest, SetFilePathTest)
{
    const MHString filePath = "test.log";

    EXPECT_NO_THROW(log.setFilePath(filePath));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get file path
/// @param MHConfigTest is test fixture
/// @param GetFilePathTest is test name
TEST_F(MHLogTest, GetFilePathTest)
{
    const MHString filePath = "test.log";
    log.setFilePath(filePath);

    EXPECT_EQ(log.getFilePath(), filePath);
}
