////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ible_client.h
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

#include <cstdint>
#include <functional>
#include <vector>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IBleClient
    /// @brief Abstract interface for low-level BLE GATT client implementations.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IBleClient {
      public:
        using NotificationCallback =
            std::function<void(const std::vector<uint8_t> &)>;

        virtual ~IBleClient() = default;

        virtual bool connect(NotificationCallback callback) = 0;
        virtual bool disconnect() = 0;
        virtual void abort() = 0;
        virtual bool isConnected() const = 0;

        virtual void write(const std::vector<uint8_t> &data) = 0;
    };
} // namespace Electux::App::Com
