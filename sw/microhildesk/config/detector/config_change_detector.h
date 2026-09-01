////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_change_detector.h
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
#pragma once

#include <config/detector/iconfig_change_detector.h>

namespace Electux::App::Config {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ConfigChangeDetector
    /// @brief Detects differences between two configuration model instances.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ConfigChangeDetector : public IConfigChangeDetector {
      public:
        ConfigChangeDetector() = default;
        ~ConfigChangeDetector() override = default;

        [[nodiscard]] ConfigChanges detectChanges(
            const Model::IModel &oldConfig,
            const Model::IModel &newConfig
        ) const override;

      private:
        [[nodiscard]] bool hasGeneralConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;

        [[nodiscard]] bool hasSerialConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;

        [[nodiscard]] bool hasTcpConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;

        [[nodiscard]] bool hasBleConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;

        [[nodiscard]] bool hasLoggerConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;

        [[nodiscard]] std::vector<size_t> findChangedChannels(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        ) const;
    };
} // namespace Electux::App::Config
