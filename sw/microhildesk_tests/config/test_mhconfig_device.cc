#include "test_mhconfig.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set device file path
/// @param MHConfigTest is test fixture
/// @param SetDeviceTest is test name
TEST_F(MHConfigTest, SetDeviceTest)
{
    const MHString device = "/dev/ttyS0";

    EXPECT_NO_THROW(m_config.setDevice(device));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get device file path
/// @param MHConfigTest is test fixture
/// @param GetDeviceTest is test name
TEST_F(MHConfigTest, GetDeviceTest)
{
    const MHString device = "/dev/ttyS0";
    m_config.setDevice(device);

    EXPECT_TRUE(m_config.getDevice() == device);
}
