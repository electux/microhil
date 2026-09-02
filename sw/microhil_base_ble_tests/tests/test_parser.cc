#include <gtest/gtest.h>
#include "command/parser.h"
#include "mocks/mocks.h"

class BleParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_ble();
        mock_clear_usb();
    }
};

TEST_F(BleParserTest, BleStreamCommand) {
    mock_push_ble_rx("<mh#ch#1#on#end>");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#ch#1#on#end");
}

TEST_F(BleParserTest, UsbSerialStreamCommand) {
    mock_push_usb_rx("<mh#ble#get#end>");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#ble#get#end");
}

TEST_F(BleParserTest, IncompleteCommand) {
    mock_push_ble_rx("<mh#ch#1#");
    char buf[64] = {0};
    EXPECT_FALSE(parser_get_command(buf, sizeof(buf)));

    mock_push_ble_rx("on#end>");
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#ch#1#on#end");
}

TEST_F(BleParserTest, IgnoresWhitespace) {
    mock_push_ble_rx("\r\n<mh#all#off#end>\r\n");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#all#off#end");
}

TEST_F(BleParserTest, BufferOverflowHandling) {
    std::string long_cmd = "<" + std::string(100, 'A') + ">";
    mock_push_ble_rx(long_cmd);
    char buf[32] = {0};
    EXPECT_FALSE(parser_get_command(buf, sizeof(buf)));
}
