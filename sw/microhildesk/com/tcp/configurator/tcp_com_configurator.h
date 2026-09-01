////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com_configurator.h
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

#include <com/icom_configurator.h>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class TcpComConfigurator
    /// @brief Configures TCP/IP communication parameters using the model.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class TcpComConfigurator : public IComConfigurator {
      public:
        TcpComConfigurator() = default;
        ~TcpComConfigurator() override = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the TCP/IP connection.
        /// @param model Reference to the configuration model.
        /// @param comChannel Reference to the communication channel interface.
        /// @return true if configuration was successful, else false.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool configure(const Model::IModel &model, ICom &comChannel) override;
    };
} // namespace Electux::App::Com
