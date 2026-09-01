////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// configurator_factory.cc
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
#include <com/ble/configurator/ble_com_configurator.h>
#include <com/configurator_factory.h>
#include <com/serial/configurator/serial_com_configurator.h>
#include <com/switchable_com_configurator.h>
#include <com/tcp/configurator/tcp_com_configurator.h>

namespace Electux::App::Com {
    std::unique_ptr<IComConfigurator> createSerialConfigurator() {
        return std::make_unique<SerialComConfigurator>();
    }

    std::unique_ptr<IComConfigurator> createTcpConfigurator() {
        return std::make_unique<TcpComConfigurator>();
    }

    std::unique_ptr<IComConfigurator> createBleConfigurator() {
        return std::make_unique<BleComConfigurator>();
    }

    std::unique_ptr<IComConfigurator> createSwitchableConfigurator(
        std::unique_ptr<IComConfigurator> serialConfigurator,
        std::unique_ptr<IComConfigurator> tcpConfigurator,
        std::unique_ptr<IComConfigurator> bleConfigurator
    ) {
        return std::make_unique<SwitchableComConfigurator>(
            std::move(serialConfigurator),
            std::move(tcpConfigurator),
            std::move(bleConfigurator)
        );
    }
} // namespace Electux::App::Com
