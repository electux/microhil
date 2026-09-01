////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller_factory.h
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

#include <com/icom.h>
#include <com/icom_configurator.h>
#include <command/formatter/icommand_formatter.h>
#include <command/mapper/ichannel_command_mapper.h>
#include <command/processor/iresponse_processor.h>
#include <config/detector/iconfig_change_detector.h>
#include <config/iconfig.h>
#include <iapp_controller.h>
#include <log/ilog.h>
#include <memory>
#include <worker/idevice_worker.h>

namespace Electux::App {
    std::unique_ptr<IAppController> createAppController(
        std::unique_ptr<Config::IConfig> configManager,
        std::unique_ptr<Worker::IDeviceWorker> deviceWorker,
        std::unique_ptr<Logger::ILog> logger,
        std::unique_ptr<Command::ICommandFormatter> commandFormatter,
        std::unique_ptr<Command::IChannelCommandMapper> channelMapper,
        std::unique_ptr<Config::IConfigChangeDetector> configDetector,
        std::unique_ptr<Command::IResponseProcessor> responseProcessor
    );

    std::unique_ptr<IAppController> createAppController(
        std::unique_ptr<Config::IConfig> configManager,
        std::unique_ptr<Com::ICom> comChannel,
        std::unique_ptr<Com::IComConfigurator> comConfigurator,
        std::unique_ptr<Logger::ILog> logger,
        std::unique_ptr<Command::ICommandFormatter> commandFormatter,
        std::unique_ptr<Command::IChannelCommandMapper> channelMapper,
        std::unique_ptr<Command::IResponseProcessor> workerResponseProcessor,
        std::unique_ptr<Command::IResponseProcessor> controllerResponseProcessor,
        std::unique_ptr<Config::IConfigChangeDetector> configDetector
    );
} // namespace Electux::App
