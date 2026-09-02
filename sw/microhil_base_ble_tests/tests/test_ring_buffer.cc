#include <gtest/gtest.h>
#include "ble/ble_ring_buffer.h"

class BleRingBufferTest : public ::testing::Test {
protected:
    enum { BUFFER_SIZE = 8 };
    uint8_t storage[BUFFER_SIZE];
    ble_ring_buffer_t rb;

    void SetUp() override {
        ble_ring_buffer_init(&rb, storage, BUFFER_SIZE);
    }
};

TEST_F(BleRingBufferTest, InitEmpty) {
    EXPECT_TRUE(ble_ring_buffer_is_empty(&rb));
    EXPECT_FALSE(ble_ring_buffer_is_full(&rb));
    EXPECT_EQ(ble_ring_buffer_available(&rb), 0u);
}

TEST_F(BleRingBufferTest, PutAndGetSingle) {
    EXPECT_TRUE(ble_ring_buffer_put(&rb, 0x42));
    EXPECT_FALSE(ble_ring_buffer_is_empty(&rb));
    EXPECT_EQ(ble_ring_buffer_available(&rb), 1u);

    uint8_t val = 0;
    EXPECT_TRUE(ble_ring_buffer_get(&rb, &val));
    EXPECT_EQ(val, 0x42);
    EXPECT_TRUE(ble_ring_buffer_is_empty(&rb));
}

TEST_F(BleRingBufferTest, FillAndOverflow) {
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        EXPECT_TRUE(ble_ring_buffer_put(&rb, i));
    }
    EXPECT_TRUE(ble_ring_buffer_is_full(&rb));
    EXPECT_EQ(ble_ring_buffer_available(&rb), static_cast<uint32_t>(BUFFER_SIZE));

    // Next put should fail
    EXPECT_FALSE(ble_ring_buffer_put(&rb, 0xFF));

    // Drain
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(ble_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }
    EXPECT_TRUE(ble_ring_buffer_is_empty(&rb));
}

TEST_F(BleRingBufferTest, WrapAround) {
    // Put 5, get 5
    for (uint8_t i = 0; i < 5; i++) {
        EXPECT_TRUE(ble_ring_buffer_put(&rb, i));
    }
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(ble_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }

    // Now head and tail are at index 5. Add 6 items (crosses wrap-around at 8)
    for (uint8_t i = 10; i < 16; i++) {
        EXPECT_TRUE(ble_ring_buffer_put(&rb, i));
    }
    EXPECT_EQ(ble_ring_buffer_available(&rb), 6u);

    for (uint8_t i = 10; i < 16; i++) {
        uint8_t val = 0;
        EXPECT_TRUE(ble_ring_buffer_get(&rb, &val));
        EXPECT_EQ(val, i);
    }
    EXPECT_TRUE(ble_ring_buffer_is_empty(&rb));
}
