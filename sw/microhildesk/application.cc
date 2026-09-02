////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application.cc
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
#include <app_controller_factory.h>
#include <application.h>
#include <com/com_factory.h>
#include <com/configurator_factory.h>
#include <command/command_factory.h>
#include <command/mapper/channel_command_mapper_factory.h>
#include <config/config_factory.h>
#include <config/detector/config_detector_factory.h>
#include <glibmm/miscutils.h>
#include <iostream>
#include <log/log_factory.h>
#include <model/model_factory.h>
#include <string_view>
#include <view/about/about.h>
#include <view/action/app_action_manager_factory.h>
#include <view/help/help.h>
#include <view/home.h>
#include <view/menu/app_menu_builder_factory.h>
#include <view/settings/settings.h>

using namespace Electux::App;

namespace {
    constexpr std::string_view cApplicationId{"com.microhil.desk"};
    constexpr std::string_view cStartupMsg{"Startup application..."};
    constexpr std::string_view cStartupDoneMsg{"Startup application done."};
    constexpr std::string_view cActivateMsg{"Activate application..."};
    constexpr std::string_view cActivateDoneMsg{"Activate application done."};
    constexpr std::string_view cShutdownMsg{"Shutting down application..."};
} // namespace

EntryApplication::EntryApplication(
    bool verbose,
    std::unique_ptr<IAppController> controller,
    std::unique_ptr<View::Menu::IAppMenuBuilder> menuBuilder,
    std::unique_ptr<View::Action::IAppActionManager> actionManager
)
    : Gtk::Application(cApplicationId.data()),
      m_verbose(verbose),
      m_controller(std::move(controller)),
      m_menuBuilder(std::move(menuBuilder)),
      m_actionManager(std::move(actionManager)) {
    if (!m_controller) {
        auto config = Model::createDefault();
        auto configManager = Config::createConfigManager(std::move(config), m_verbose);
        auto configDetector = Config::createConfigChangeDetector();

        auto serial = Com::createSerialCom(m_verbose);
        auto tcp = Com::createTcpCom(m_verbose);
        auto ble = Com::createBleCom(m_verbose);

        auto switchableCom = Com::createSwitchableCom(
            m_verbose, std::move(serial), std::move(tcp), std::move(ble)
        );

        auto configurator = Com::createSwitchableConfigurator(
            Com::createSerialConfigurator(),
            Com::createTcpConfigurator(),
            Com::createBleConfigurator()
        );

        auto logger = Logger::createLogger();
        auto commandFormatter = Command::createCommandFormatter();
        auto channelMapper = Command::createChannelCommandMapper();
        auto workerResponseProcessor = Command::createResponseProcessor();
        auto controllerResponseProcessor = Command::createResponseProcessor();

        m_controller = createAppController(
            std::move(configManager), std::move(switchableCom),
            std::move(configurator), std::move(logger),
            std::move(commandFormatter), std::move(channelMapper),
            std::move(workerResponseProcessor),
            std::move(controllerResponseProcessor),
            std::move(configDetector)
        );
    }

    if (!m_menuBuilder) {
        m_menuBuilder = View::Menu::createAppMenuBuilder();
    }

    if (!m_actionManager) {
        m_actionManager = View::Action::createAppActionManager();
    }

    Glib::set_application_name(cApplicationId.data());
}

EntryApplication::~EntryApplication() = default;

Glib::RefPtr<EntryApplication> EntryApplication::create(bool verbose) {
    return Glib::make_refptr_for_instance<EntryApplication>(
        new EntryApplication(verbose)
    );
}

void EntryApplication::on_startup() {
    if (m_verbose) {
        std::cout << cStartupMsg << std::endl;
    }
    Gtk::Application::on_startup();

    m_home = std::make_unique<View::AppHome>();
    m_settings = std::make_unique<View::Settings::AppSettings>();
    m_help = std::make_unique<View::Help::AppHelp>();
    m_about = std::make_unique<View::About::AppAbout>();

    m_controller->startup();

    if (m_menuBuilder) {
        set_menubar(m_menuBuilder->buildMenu());
    }

    if (m_actionManager) {
        View::Action::AppViewsContext viewsCtx{
            m_home.get(), m_settings.get(), m_help.get(), m_about.get()
        };
        m_actionManager->registerActions(*this, *m_controller, viewsCtx);
    }

    m_home->connect_close_request(
        sigc::mem_fun(*this, &EntryApplication::onHandleClose)
    );
    m_settings->setupChanged().connect(
        sigc::mem_fun(*this, &EntryApplication::onSetupChanged)
    );
    m_home->channelChanged().connect(
        sigc::mem_fun(*m_controller, &IAppController::onChannelStateChanged)
    );
    m_home->controlChanged().connect(
        sigc::mem_fun(*this, &EntryApplication::onSetupChanged)
    );
    m_controller->signal_data_received().connect(
        sigc::mem_fun(*m_home, &View::IHomeView::postData)
    );
    m_controller->signal_connection_state().connect(
        sigc::mem_fun(*m_home, &View::IHomeView::setConnectionState)
    );

    add_window(m_home->getGtkWindow());
    m_settings->getGtkWindow().set_transient_for(m_home->getGtkWindow());
    m_help->getGtkWindow().set_transient_for(m_home->getGtkWindow());
    m_about->getGtkWindow().set_transient_for(m_home->getGtkWindow());

    m_controller->getModel().signal_changed().connect([this]() {
        SettingsSetup setup;
        setup.m_config = m_controller->getModel().clone();
        m_settings->setSettingsSetup(setup);
        m_settings->updateUiData();
        m_home->setControlSetup(setup);
        m_home->updateUiData();
    });

    SettingsSetup setup;
    setup.m_config = m_controller->getModel().clone();
    m_settings->setSettingsSetup(setup);
    m_settings->updateUiData();
    m_home->setControlSetup(setup);
    m_home->updateUiData();

    if (m_verbose) {
        std::cout << cStartupDoneMsg << std::endl;
    }
}

void EntryApplication::on_activate() {
    if (m_verbose) {
        std::cout << cActivateMsg << std::endl;
    }
    Gtk::Application::on_activate();
    m_home->show();
    if (m_verbose) {
        std::cout << cActivateDoneMsg << std::endl;
    }
}

void EntryApplication::on_shutdown() {
    if (m_verbose) {
        std::cout << cShutdownMsg << std::endl;
    }
    m_controller->shutdown();
    Gtk::Application::on_shutdown();
}

bool EntryApplication::onHandleClose() {
    if (m_home) {
        m_home->hide();
    }
    if (m_settings) {
        m_settings->hide();
    }
    quit();
    return false;
}

void EntryApplication::onSetupChanged(const SettingsSetup &setup) {
    m_controller->onSetupChanged(setup);
}
