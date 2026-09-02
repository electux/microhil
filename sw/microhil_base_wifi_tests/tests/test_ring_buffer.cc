#include <gtest/gtest.h>
#include "wifi/wifi_ring_buffer.h"

class WifiRingBufferTest : public ::testing::Test {
protected:
    enum { BUFFER_SIZE = 8 };
    uint8_t storage[BUFFER_SIZE];
    wifi_ring_buffer_t rb;

    void SetUp() override {
        wifi_ring_buffer_init(&rb, storage, BUFFER_SIZE);
    }
};

TEST_F(WifiRingBufferTest, InitEmpty) {
    EXPECT_TRUE(wifi_ring_buffer_is_empty(&rb));
    EXPECT_FALSE(wifi_ring_buffer_is_full(&rb));
    EXPECT_EQ(wifi_ring_buffer_available(&rb), 0u);
}

TEST_F(WifiRingBufferTest, PutAndGetSingle) {
    EXPECT_TRUE(wifi_ring_buffer_put(&rb, 0x55));
    EXPECT_FALSE(wifi_ring_buffer_is_empty(&rb));
    EXPECT_EQ(wifi_ring_buffer_available(&rb), 1u);

    uint8_t val = 0;
    EXPECT_TRUE(wifi_ring_buffer_get(&rb, &val));
    EXPECT_EQ(val, 0x55);
    EXPECT_TRUE(wifi_ring_buffer_is_empty(&rb));
}

TEST_F(WifiRingBufferTest, FillAndOverflow) {
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        EXPECT_TRUE(wifi_ring_buffer_put(&rb, i));
    }
    EXPECT_TRUE(wifi_ring_buffer_is_full(&rb));
    EXPECT_EQ(wifi_ring_buffer_available(&rb), static_cast<uint32_t>(BUFFER_SIZE));

    // Next put should fail
    EXPECT_FALSE(wifi_ring_buffer_put(&rb, 0xFF));

    // Drain
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(wifi_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }
    EXPECT_TRUE(wifi_ring_buffer_is_empty(&rb));
}

TEST_F(WifiRingBufferTest, WrapAround) {
    for (uint8_t i = 0; i < 5; i++) {
        EXPECT_TRUE(wifi_ring_buffer_put(&rb, i));
    }
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(wifi_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }

    for (uint8_t i = 10; i < 16; i++) {
        EXPECT_TRUE(wifi_ring_buffer_put(&rb, i));
    }
    EXPECT_EQ(wifi_ring_buffer_available(&rb), 6u);

    for (uint8_t i = 10; i < 16; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(wifi_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }
    EXPECT_TRUE(wifi_ring_buffer_is_empty(&rb));
}
