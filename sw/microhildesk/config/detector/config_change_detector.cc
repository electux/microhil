////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_change_detector.cc
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

#include <config/detector/config_change_detector.h>
#include <model/channel_types.h>
#include <model/model_types.h>

using namespace Electux::App::Config;
using namespace Electux::App::Model;

ConfigChanges ConfigChangeDetector::detectChanges(
    const IModel &oldConfig, const IModel &newConfig
) const {
    ConfigChanges changes;
    changes.generalChanged = hasGeneralConfigChanged(oldConfig, newConfig);
    changes.serialChanged = hasSerialConfigChanged(oldConfig, newConfig);
    changes.tcpChanged = hasTcpConfigChanged(oldConfig, newConfig);
    changes.bleChanged = hasBleConfigChanged(oldConfig, newConfig);
    changes.logChanged = hasLoggerConfigChanged(oldConfig, newConfig);
    changes.changedChannels = findChangedChannels(oldConfig, newConfig);

    return changes;
}

bool ConfigChangeDetector::hasGeneralConfigChanged(
    const IModel &oldConfig, const IModel &newConfig
) const {
    for (int k = static_cast<int>(ModelGeneralKey::ComType);
         k <= static_cast<int>(ModelGeneralKey::TcpPort); ++k) {
        auto key = oldConfig.toString(static_cast<ModelGeneralKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }

    return false;
}

bool ConfigChangeDetector::hasSerialConfigChanged(
    const IModel &oldConfig, const IModel &newConfig
) const {
    for (int k = static_cast<int>(ModelSerialKey::Device);
         k <= static_cast<int>(ModelSerialKey::Flow); ++k) {
        auto key = oldConfig.toString(static_cast<ModelSerialKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }

    return false;
}

bool ConfigChangeDetector::hasTcpConfigChanged(
    const IModel &oldConfig, const IModel &newConfig
) const {
    for (int k = static_cast<int>(ModelGeneralKey::TcpIp);
         k <= static_cast<int>(ModelGeneralKey::TcpPort); ++k) {
        auto key = oldConfig.toString(static_cast<ModelGeneralKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }

    return false;
}

bool ConfigChangeDetector::hasBleConfigChanged(
    const IModel &oldConfig, const IModel &newConfig
) const {
    for (int k = static_cast<int>(ModelBleKey::Address);
         k <= static_cast<int>(ModelBleKey::TxUuid); ++k) {
        auto key = oldConfig.toString(static_cast<ModelBleKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }

    return false;
}

bool ConfigChangeDetector::hasLoggerConfigChanged(
    const IModel &oldConfig, const IModel &newConfig
) const {
    for (int k = static_cast<int>(ModelLogKey::FilePath);
         k <= static_cast<int>(ModelLogKey::LogLevel); ++k) {
        auto key = oldConfig.toString(static_cast<ModelLogKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }

    return false;
}

std::vector<size_t> ConfigChangeDetector::findChangedChannels(
    const IModel &oldConfig, const IModel &newConfig
) const {
    std::vector<size_t> changed;
    for (size_t i = 0; i < Channel::cNumOfChannels; ++i) {
        const auto &oldState = oldConfig.getChannelState(i);
        const auto &newState = newConfig.getChannelState(i);

        if (oldState != newState) {
            changed.push_back(i);
        }
    }

    return changed;
}
