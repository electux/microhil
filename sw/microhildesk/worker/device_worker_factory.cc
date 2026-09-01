////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// device_worker_factory.cc
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
#include <com/com_factory.h>
#include <com/configurator_factory.h>
#include <command/command_factory.h>
#include <worker/device_worker.h>
#include <worker/device_worker_factory.h>

namespace Electux::App::Worker {
    std::unique_ptr<IDeviceWorker> createDeviceWorker(
        std::unique_ptr<Com::ICom> comChannel,
        std::unique_ptr<Com::IComConfigurator> comConfigurator,
        std::unique_ptr<Command::ICommandFormatter> commandFormatter,
        std::unique_ptr<Command::IResponseProcessor> responseProcessor,
        Logger::ILog *logger
    ) {
        if (!comChannel) {
            auto serial = Com::createSerialCom();
            auto tcp = Com::createTcpCom();
            auto ble = Com::createBleCom();

            auto switchableCom = Com::createSwitchableCom(
                false, std::move(serial), std::move(tcp), std::move(ble)
            );

            if (!comConfigurator) {
                comConfigurator = Com::createSwitchableConfigurator(
                    Com::createSerialConfigurator(),
                    Com::createTcpConfigurator(),
                    Com::createBleConfigurator()
                );
            }
            comChannel = std::move(switchableCom);
        }
        if (!commandFormatter) {
            commandFormatter = Command::createCommandFormatter();
        }
        if (!responseProcessor) {
            responseProcessor = Command::createResponseProcessor();
        }

        return std::make_unique<DeviceWorker>(
            std::move(comChannel),
            std::move(comConfigurator),
            std::move(commandFormatter),
            std::move(responseProcessor),
            logger
        );
    }
} // namespace Electux::App::Worker
