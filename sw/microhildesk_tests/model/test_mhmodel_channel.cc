#include "test_mhmodel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test set channel
/// @param MHModelTest is test fixture
/// @param SetChannelTest is test name
TEST_F(MHModelTest, SetChannelTest)
{
    EXPECT_NO_THROW(model.setChannel(0, ChannelState::MICROHIL_ON));
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test get channel
/// @param MHModelTest is test fixture
/// @param GetChannelTest is test name
TEST_F(MHModelTest, GetChannelTest)
{
    model.setChannel(0, ChannelState::MICROHIL_ON);
    EXPECT_EQ(model.getChannel(0), ChannelState::MICROHIL_ON);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test is channel on
/// @param MHModelTest is test fixture
/// @param IsChannelOnTest is test name
TEST_F(MHModelTest, IsChannelOnTest)
{
    model.setChannel(0, ChannelState::MICROHIL_ON);
    EXPECT_TRUE(model.isOnChannel(0));
}
