#include <gtest/gtest.h>
#include "config/nvm_config.h"
#include "mocks/mocks.h"
#include <cstring>

class NvmConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_flash();
    }
};

TEST_F(NvmConfigTest, UninitializedFlashReturnsDefault) {
    nvm_wifi_config_t cfg;
    nvm_config_init(&cfg);

    EXPECT_EQ(cfg.mode, (uint8_t)WIFI_MODE_AP);
    EXPECT_STREQ(cfg.ssid, "microhil-wifi");
    EXPECT_STREQ(cfg.password, "microhil123");
    EXPECT_STREQ(cfg.ip, "192.168.4.1");
    EXPECT_EQ(cfg.port, 5000);
}

TEST_F(NvmConfigTest, SaveAndReloadConfig) {
    nvm_wifi_config_t new_cfg;
    memset(&new_cfg, 0, sizeof(new_cfg));
    new_cfg.mode = (uint8_t)WIFI_MODE_STA;
    strncpy(new_cfg.ssid, "MyHomeSSID", sizeof(new_cfg.ssid) - 1);
    strncpy(new_cfg.password, "SecretPass123", sizeof(new_cfg.password) - 1);
    strncpy(new_cfg.ip, "0.0.0.0", sizeof(new_cfg.ip) - 1);
    new_cfg.port = 8080;

    EXPECT_TRUE(nvm_config_save(&new_cfg));

    nvm_wifi_config_t loaded_cfg;
    nvm_config_init(&loaded_cfg);

    EXPECT_EQ(loaded_cfg.mode, (uint8_t)WIFI_MODE_STA);
    EXPECT_STREQ(loaded_cfg.ssid, "MyHomeSSID");
    EXPECT_STREQ(loaded_cfg.password, "SecretPass123");
    EXPECT_EQ(loaded_cfg.port, 8080);
}

TEST_F(NvmConfigTest, CorruptedFlashRecoversToDefault) {
    nvm_wifi_config_t new_cfg;
    nvm_config_get_default(&new_cfg);
    EXPECT_TRUE(nvm_config_save(&new_cfg));

    // Corrupt one byte in the flash memory where config is stored
    uint32_t flash_offset = PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE;
    mock_flash_storage[flash_offset + 10] ^= 0xFF;

    nvm_wifi_config_t loaded_cfg;
    nvm_config_init(&loaded_cfg);

    // Should fall back safely to defaults
    EXPECT_EQ(loaded_cfg.mode, (uint8_t)WIFI_MODE_AP);
    EXPECT_STREQ(loaded_cfg.ssid, "microhil-wifi");
}

TEST_F(NvmConfigTest, ResetToDefault) {
    nvm_wifi_config_t custom_cfg;
    memset(&custom_cfg, 0, sizeof(custom_cfg));
    custom_cfg.mode = (uint8_t)WIFI_MODE_STA;
    strncpy(custom_cfg.ssid, "Temporary", sizeof(custom_cfg.ssid) - 1);
    nvm_config_save(&custom_cfg);

    EXPECT_TRUE(nvm_config_reset_to_default());

    nvm_wifi_config_t reloaded;
    nvm_config_init(&reloaded);
    EXPECT_EQ(reloaded.mode, (uint8_t)WIFI_MODE_AP);
    EXPECT_STREQ(reloaded.ssid, "microhil-wifi");
}
