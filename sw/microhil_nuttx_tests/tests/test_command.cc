#include "gtest/gtest.h"
extern "C" {
#include "command/microhil_cmd.h"
}

TEST(CommandParseTest, SystemCommands) {
    microhil_cmd_t cmd;
    EXPECT_TRUE(microhil_cmd_parse("mh#sys#id#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_SYS_ID);

    EXPECT_TRUE(microhil_cmd_parse("mh#sys#version#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_SYS_VERSION);

    EXPECT_TRUE(microhil_cmd_parse("mh#sys#reset#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_SYS_RESET);
}

TEST(CommandParseTest, GlobalCommands) {
    microhil_cmd_t cmd;
    EXPECT_TRUE(microhil_cmd_parse("mh#all#on#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_ALL_ON);

    EXPECT_TRUE(microhil_cmd_parse("mh#all#off#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_ALL_OFF);

    EXPECT_TRUE(microhil_cmd_parse("mh#all#stat#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_ALL_STAT);
}

TEST(CommandParseTest, ChannelControl) {
    microhil_cmd_t cmd;
    EXPECT_TRUE(microhil_cmd_parse("mh#ch#1#on#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_CH_ON);
    EXPECT_EQ(cmd.data.ch.ch_idx, 0);

    EXPECT_TRUE(microhil_cmd_parse("mh#ch#8#off#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_CH_OFF);
    EXPECT_EQ(cmd.data.ch.ch_idx, 7);
}

TEST(CommandParseTest, TimerPulseBlink) {
    microhil_cmd_t cmd;
    EXPECT_TRUE(microhil_cmd_parse("mh#ch#3#tmr#15#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_CH_TMR);
    EXPECT_EQ(cmd.data.ch.ch_idx, 2);
    EXPECT_EQ(cmd.data.ch.args.timer_sec, 15);

    EXPECT_TRUE(microhil_cmd_parse("mh#ch#5#pulse#250#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_CH_PULSE);
    EXPECT_EQ(cmd.data.ch.ch_idx, 4);
    EXPECT_EQ(cmd.data.ch.args.pulse_ms, 250);

    EXPECT_TRUE(microhil_cmd_parse("mh#ch#2#blink#100#200#5#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_CH_BLINK);
    EXPECT_EQ(cmd.data.ch.ch_idx, 1);
    EXPECT_EQ(cmd.data.ch.args.blink.on_ms, 100);
    EXPECT_EQ(cmd.data.ch.args.blink.off_ms, 200);
    EXPECT_EQ(cmd.data.ch.args.blink.count, 5);
}

TEST(CommandParseTest, MaskCommand) {
    microhil_cmd_t cmd;
    EXPECT_TRUE(microhil_cmd_parse("mh#all#mask#10101010#end", &cmd));
    EXPECT_EQ(cmd.type, CMD_TYPE_ALL_MASK);
    EXPECT_STREQ(cmd.data.mask, "10101010");
}

TEST(CommandParseTest, InvalidCommands) {
    microhil_cmd_t cmd;
    EXPECT_FALSE(microhil_cmd_parse("invalid", &cmd));
    EXPECT_FALSE(microhil_cmd_parse("mh#ch#9#on#end", &cmd));
    EXPECT_FALSE(microhil_cmd_parse("mh#ch#1#tmr#abc#end", &cmd));
}
