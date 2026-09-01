////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iconfig_change_detector.h
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

#include <model/imodel.h>
#include <vector>
#include <cstddef>

namespace Electux::App::Config {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @struct ConfigChanges
    /// @brief Holds diff flags across all functional sections of application models.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    struct ConfigChanges {
        bool generalChanged{false};
        bool serialChanged{false};
        bool tcpChanged{false};
        bool bleChanged{false};
        bool logChanged{false};
        std::vector<size_t> changedChannels;

        [[nodiscard]] bool hasComChanged() const noexcept {
            return generalChanged || serialChanged || tcpChanged || bleChanged;
        }

        [[nodiscard]] bool anyChanged() const noexcept {
            return generalChanged || serialChanged || tcpChanged || bleChanged ||
                   logChanged || !changedChannels.empty();
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IConfigChangeDetector
    /// @brief Interface for detecting changes between two Model instances.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IConfigChangeDetector {
      public:
        virtual ~IConfigChangeDetector() = default;

        [[nodiscard]] virtual ConfigChanges detectChanges(
            const Model::IModel &oldConfig,
            const Model::IModel &newConfig
        ) const = 0;
    };
} // namespace Electux::App::Config
