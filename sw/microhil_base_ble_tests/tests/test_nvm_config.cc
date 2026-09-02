#include <gtest/gtest.h>
#include "config/nvm_config.h"
#include "config/ble_default_config.h"
#include "mocks/mocks.h"
#include "mocks/hardware/flash.h"
#include <cstring>

class NvmBleConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_flash_reset(true); // default erased flash (0xFF)
    }
};

TEST_F(NvmBleConfigTest, UninitializedFlashReturnsDefault) {
    bool valid = nvm_config_init();
    EXPECT_FALSE(valid);

    const nvm_ble_config_t *cfg = nvm_config_get();
    ASSERT_NE(cfg, nullptr);
    EXPECT_EQ(cfg->magic, NVM_BLE_MAGIC);
    EXPECT_STREQ(cfg->device_name, DEFAULT_BLE_DEVICE_NAME);
    EXPECT_EQ(cfg->adv_interval_ms, DEFAULT_BLE_ADV_INTERVAL_MS);
    EXPECT_EQ(cfg->passkey, DEFAULT_BLE_PASSKEY);
}

TEST_F(NvmBleConfigTest, SaveAndReloadConfig) {
    nvm_ble_config_t custom_cfg;
    memset(&custom_cfg, 0, sizeof(custom_cfg));
    strncpy(custom_cfg.device_name, "microhil-lab42", sizeof(custom_cfg.device_name) - 1);
    custom_cfg.adv_interval_ms = 100;
    custom_cfg.passkey = 654321;

    bool saved = nvm_config_save(&custom_cfg);
    EXPECT_TRUE(saved);

    const nvm_ble_config_t *loaded = nvm_config_get();
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->magic, NVM_BLE_MAGIC);
    EXPECT_STREQ(loaded->device_name, "microhil-lab42");
    EXPECT_EQ(loaded->adv_interval_ms, 100);
    EXPECT_EQ(loaded->passkey, 654321);
}

TEST_F(NvmBleConfigTest, CorruptedFlashRecoversToDefault) {
    nvm_ble_config_t custom_cfg;
    memset(&custom_cfg, 0, sizeof(custom_cfg));
    strncpy(custom_cfg.device_name, "microhil-corrupt", sizeof(custom_cfg.device_name) - 1);
    custom_cfg.adv_interval_ms = 80;
    custom_cfg.passkey = 111111;

    nvm_config_save(&custom_cfg);

    // Intentionally corrupt a byte in the flash config sector
    uint32_t offset = PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE;
    mock_flash_storage[offset + 10] ^= 0x55;

    bool valid = nvm_config_init();
    EXPECT_FALSE(valid);

    const nvm_ble_config_t *loaded = nvm_config_get();
    EXPECT_STREQ(loaded->device_name, DEFAULT_BLE_DEVICE_NAME);
}

TEST_F(NvmBleConfigTest, ResetToDefault) {
    nvm_ble_config_t custom_cfg;
    memset(&custom_cfg, 0, sizeof(custom_cfg));
    strncpy(custom_cfg.device_name, "microhil-temp", sizeof(custom_cfg.device_name) - 1);
    nvm_config_save(&custom_cfg);

    bool reset_ok = nvm_config_reset_to_default();
    EXPECT_TRUE(reset_ok);

    const nvm_ble_config_t *loaded = nvm_config_get();
    EXPECT_STREQ(loaded->device_name, DEFAULT_BLE_DEVICE_NAME);
}
