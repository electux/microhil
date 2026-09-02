#include <gtest/gtest.h>
#include "command/parser.h"
#include "mocks/mocks.h"

class WifiParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_wifi();
        mock_clear_usb();
    }
};

TEST_F(WifiParserTest, WifiStreamCommand) {
    mock_push_wifi_rx("<mh#ch#1#on#end>");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#ch#1#on#end");
}

TEST_F(WifiParserTest, UsbSerialStreamCommand) {
    mock_push_usb_rx("<mh#net#get#end>");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#net#get#end");
}

TEST_F(WifiParserTest, IncompleteAndReassembly) {
    mock_push_wifi_rx("<mh#ch#2#");
    char buf[64] = {0};
    EXPECT_FALSE(parser_get_command(buf, sizeof(buf)));

    mock_push_wifi_rx("off#end>");
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#ch#2#off#end");
}

TEST_F(WifiParserTest, IgnoresWhitespace) {
    mock_push_usb_rx("\r\n<mh#all#off#end>\r\n");
    char buf[64] = {0};
    EXPECT_TRUE(parser_get_command(buf, sizeof(buf)));
    EXPECT_STREQ(buf, "mh#all#off#end");
}

TEST_F(WifiParserTest, BufferOverflowHandling) {
    std::string long_cmd = "<" + std::string(100, 'A') + ">";
    mock_push_wifi_rx(long_cmd);
    char buf[32] = {0};
    EXPECT_FALSE(parser_get_command(buf, sizeof(buf)));
}
