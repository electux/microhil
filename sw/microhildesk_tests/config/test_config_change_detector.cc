////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_change_detector.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <config/config_manager.h>
#include <config/detector/config_detector_factory.h>
#include <model/model_factory.h>
#include <model/model_types.h>
#include <model/channel_state.h>
#include <string_view>

using namespace Electux::App;
using namespace Electux::App::Config;
using namespace Electux::App::Model;

namespace {
    constexpr std::string_view cAltDevice{"/dev/ttyUSB1"};
    constexpr std::string_view cAltLogLevel{"1"};
    constexpr std::string_view cAltComType{"1"};
    constexpr std::string_view cAltBleAddr{"AA:BB:CC:DD:EE:FF"};
    constexpr size_t cTestChannelIndex{2};
    constexpr int cTestTimerValue{5000};
    constexpr std::string_view cTestTempConfigFile{"/tmp/test_diff_config.ini"};

    void setOrUpdate(IModel &model, std::string_view key, std::string_view val) {
        if (!model.update(key, val)) {
            model.add(key, val);
        }
    }
} // namespace

class ConfigChangeDetectorTest : public ::testing::Test {
  protected:
    void SetUp() override {
        m_detector = createConfigChangeDetector();
        auto cm = std::make_unique<ConfigManager>(
            createDefault(), std::string(cTestTempConfigFile)
        );
        cm->init();
        m_model1 = cm->getConfig().clone();
        m_model2 = cm->getConfig().clone();
    }

    std::unique_ptr<IConfigChangeDetector> m_detector;
    std::unique_ptr<IModel> m_model1;
    std::unique_ptr<IModel> m_model2;
};

TEST_F(ConfigChangeDetectorTest, IdenticalConfigsNoChanges) {
    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_FALSE(changes.anyChanged());
    EXPECT_FALSE(changes.generalChanged);
    EXPECT_FALSE(changes.serialChanged);
    EXPECT_FALSE(changes.tcpChanged);
    EXPECT_FALSE(changes.bleChanged);
    EXPECT_FALSE(changes.logChanged);
    EXPECT_TRUE(changes.changedChannels.empty());
}

TEST_F(ConfigChangeDetectorTest, SerialConfigChanged) {
    auto devKey = m_model2->toString(ModelSerialKey::Device);
    setOrUpdate(*m_model2, devKey, cAltDevice);

    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_TRUE(changes.anyChanged());
    EXPECT_TRUE(changes.serialChanged);
    EXPECT_TRUE(changes.hasComChanged());
    EXPECT_FALSE(changes.logChanged);
}

TEST_F(ConfigChangeDetectorTest, LogConfigChanged) {
    auto logKey = m_model2->toString(ModelLogKey::LogLevel);
    setOrUpdate(*m_model2, logKey, cAltLogLevel);

    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_TRUE(changes.anyChanged());
    EXPECT_TRUE(changes.logChanged);
    EXPECT_FALSE(changes.hasComChanged());
}

TEST_F(ConfigChangeDetectorTest, GeneralConfigChanged) {
    auto comKey = m_model2->toString(ModelGeneralKey::ComType);
    setOrUpdate(*m_model2, comKey, cAltComType);

    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_TRUE(changes.anyChanged());
    EXPECT_TRUE(changes.generalChanged);
    EXPECT_TRUE(changes.hasComChanged());
}

TEST_F(ConfigChangeDetectorTest, BleConfigChanged) {
    auto bleKey = m_model2->toString(ModelBleKey::Address);
    setOrUpdate(*m_model2, bleKey, cAltBleAddr);

    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_TRUE(changes.anyChanged());
    EXPECT_TRUE(changes.bleChanged);
    EXPECT_TRUE(changes.hasComChanged());
}

TEST_F(ConfigChangeDetectorTest, ChannelStateChanged) {
    auto state = m_model2->getChannelState(cTestChannelIndex);
    state.enabled = true;
    state.mode = Channel::ChannelMode::Timer;
    state.timer = cTestTimerValue;
    m_model2->setChannelState(cTestChannelIndex, state);

    auto changes = m_detector->detectChanges(*m_model1, *m_model2);
    EXPECT_TRUE(changes.anyChanged());
    ASSERT_EQ(changes.changedChannels.size(), 1u);
    EXPECT_EQ(changes.changedChannels[0], cTestChannelIndex);
}
