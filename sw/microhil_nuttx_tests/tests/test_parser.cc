#include "gtest/gtest.h"
extern "C" {
#include "command/microhil_parser.h"
}

class ParserTest : public ::testing::Test {
protected:
    microhil_parser_t parser;
    void SetUp() override {
        microhil_parser_init(&parser);
    }
};

TEST_F(ParserTest, WellFormedCommand) {
    std::string input = "<mh#ch#1#on#end>";
    char out_buf[128];
    bool parsed = false;
    for (char c : input) {
        if (microhil_parser_feed(&parser, c, out_buf, sizeof(out_buf))) {
            parsed = true;
        }
    }
    EXPECT_TRUE(parsed);
    EXPECT_STREQ(out_buf, "mh#ch#1#on#end");
}

TEST_F(ParserTest, IncompleteCommand) {
    std::string input = "<mh#ch#1";
    char out_buf[128];
    bool parsed = false;
    for (char c : input) {
        if (microhil_parser_feed(&parser, c, out_buf, sizeof(out_buf))) {
            parsed = true;
        }
    }
    EXPECT_FALSE(parsed);
}

TEST_F(ParserTest, IgnoreWhitespace) {
    std::string input = "\r\n<mh#all#on#end>\n";
    char out_buf[128];
    bool parsed = false;
    for (char c : input) {
        if (microhil_parser_feed(&parser, c, out_buf, sizeof(out_buf))) {
            parsed = true;
        }
    }
    EXPECT_TRUE(parsed);
    EXPECT_STREQ(out_buf, "mh#all#on#end");
}

TEST_F(ParserTest, BufferOverflow) {
    // Write characters larger than parser buffer limit
    char out_buf[128];
    microhil_parser_feed(&parser, '<', out_buf, sizeof(out_buf));
    for (int i = 0; i < MICROHIL_REQ_MAX_LEN + 10; i++) {
        microhil_parser_feed(&parser, 'A', out_buf, sizeof(out_buf));
    }
    // Feed end delimiter, it should not trigger parsed successfully since it reset
    bool parsed = microhil_parser_feed(&parser, '>', out_buf, sizeof(out_buf));
    EXPECT_FALSE(parsed);
}
