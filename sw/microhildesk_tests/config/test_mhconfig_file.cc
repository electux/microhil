#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set log file path
/// @param MHConfigTest is test fixture
/// @param SetFileTest is test name
TEST_F(MHConfigTest, SetFileTest)
{
    const MHString log_file = "/tmp/microhil.log";

    EXPECT_NO_THROW(m_config.setLogPath(log_file));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get log file path
/// @param MHConfigTest is test fixture
/// @param GetFileTest is test name
TEST_F(MHConfigTest, GetFileTest)
{
    const MHString log_file = "/tmp/microhil.log";
    m_config.setLogPath(log_file);

    EXPECT_TRUE(m_config.getLogPath() == log_file);
}
