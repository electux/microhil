////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.h
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

#include <config/iconfig.h>
#include <iapp_controller.h>
#include <memory>
#include <model/imodel.h>
#include <view/settings_setup.h>

namespace Electux::App::Com {
    class ICom;
    class IComConfigurator;
} // namespace Electux::App::Com
namespace Electux::App::Logger {
    class ILog;
}
namespace Electux::App::Command {
    class ICommandFormatter;
}

namespace Electux::App {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppController
    /// @brief Coordination controller managing config loading, storing, and
    /// model change propagation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppController : public IAppController {
      public:
        AppController(
            std::unique_ptr<Config::IConfig> configManager,
            std::unique_ptr<Com::ICom> comChannel,
            std::unique_ptr<Com::IComConfigurator> comConfigurator,
            std::unique_ptr<Logger::ILog> logger,
            std::unique_ptr<Command::ICommandFormatter> commandFormatter
        );
        virtual ~AppController() override;

        AppController(const AppController &) = delete;
        AppController &operator=(const AppController &) = delete;

        void startup() override;
        void shutdown() override;

        const Model::IModel &getModel() const override;

        void onSetupChanged(const Model::SettingsSetup &setup) override;

      private:
        void configureLogger();
        void configureComChannel();
        void handleChannelStateChanges(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        );
        bool hasSerialConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        );
        bool hasGeneralConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        );
        bool hasBleConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        );
        bool hasLoggerConfigChanged(
            const Model::IModel &oldConfig, const Model::IModel &newConfig
        );

        std::unique_ptr<Config::IConfig> m_configManager;
        std::unique_ptr<Com::ICom> m_comChannel;
        std::unique_ptr<Com::IComConfigurator> m_comConfigurator;
        std::unique_ptr<Logger::ILog> m_logger;
        std::unique_ptr<Command::ICommandFormatter> m_commandFormatter;
    };
} // namespace Electux::App
