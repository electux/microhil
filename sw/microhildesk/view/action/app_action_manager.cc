////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_action_manager.cc
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
#include <string_view>
#include <view/action/app_action_manager.h>

using namespace Electux::App::View::Action;

namespace {
    constexpr std::string_view cFileQuitActionName{"file_quit"};
    constexpr std::string_view cOptionSettingsActionName{"option_settings"};
    constexpr std::string_view cDeviceConnectActionName{"device_connect"};
    constexpr std::string_view cDeviceDisconnectActionName{"device_disconnect"};
    constexpr std::string_view cCmdAllOnActionName{"cmd_all_on"};
    constexpr std::string_view cCmdAllOffActionName{"cmd_all_off"};
    constexpr std::string_view cCmdAllStatActionName{"cmd_all_stat"};
    constexpr std::string_view cCmdSysResetActionName{"cmd_sys_reset"};
    constexpr std::string_view cCmdSysIdActionName{"cmd_sys_id"};
    constexpr std::string_view cCmdSysVersionActionName{"cmd_sys_version"};
    constexpr std::string_view cHelpDocActionName{"doc"};
    constexpr std::string_view cHelpAboutActionName{"about"};

    constexpr std::string_view cDetailedQuitAction{"app.file_quit"};
    constexpr std::string_view cQuitAccelerator{"<Primary>q"};
    constexpr std::string_view cDetailedConnectAction{"app.device_connect"};
    constexpr std::string_view cConnectAccelerator{"<Primary>k"};
    constexpr std::string_view cDetailedDisconnectAction{"app.device_disconnect"};
    constexpr std::string_view cDisconnectAccelerator{"<Primary>d"};
    constexpr std::string_view cDetailedClearAction{"app.console_clear"};
    constexpr std::string_view cClearAccelerator{"<Primary>l"};
    constexpr std::string_view cConsoleClearActionName{"console_clear"};
} // namespace

void AppActionManager::registerActions(
    Gtk::Application &app,
    IAppController &controller,
    const AppViewsContext &views
) {
    app.set_accel_for_action(
        cDetailedQuitAction.data(), cQuitAccelerator.data()
    );
    app.set_accel_for_action(
        cDetailedConnectAction.data(), cConnectAccelerator.data()
    );
    app.set_accel_for_action(
        cDetailedDisconnectAction.data(), cDisconnectAccelerator.data()
    );
    app.set_accel_for_action(
        cDetailedClearAction.data(), cClearAccelerator.data()
    );

    app.add_action(
        cFileQuitActionName.data(),
        [&app, views]() {
            if (views.home) {
                views.home->hide();
            }
            if (views.settings) {
                views.settings->hide();
            }
            app.quit();
        }
    );

    app.add_action(
        cOptionSettingsActionName.data(),
        [views]() {
            if (views.settings) {
                views.settings->show();
            }
        }
    );

    app.add_action(
        cDeviceConnectActionName.data(),
        [&controller]() {
            controller.connectDevice();
        }
    );

    app.add_action(
        cDeviceDisconnectActionName.data(),
        [&controller]() {
            controller.disconnectDevice();
        }
    );

    app.add_action(
        cConsoleClearActionName.data(),
        [views]() {
            if (views.home) {
                views.home->clearConsole();
            }
        }
    );

    app.add_action(
        cCmdAllOnActionName.data(),
        [&controller]() {
            controller.turnOnAllChannels();
        }
    );

    app.add_action(
        cCmdAllOffActionName.data(),
        [&controller]() {
            controller.turnOffAllChannels();
        }
    );

    app.add_action(
        cCmdAllStatActionName.data(),
        [&controller]() {
            controller.requestAllChannelsStatus();
        }
    );

    app.add_action(
        cCmdSysResetActionName.data(),
        [&controller]() {
            controller.resetSystem();
        }
    );

    app.add_action(
        cCmdSysIdActionName.data(),
        [&controller]() {
            controller.requestBoardId();
        }
    );

    app.add_action(
        cCmdSysVersionActionName.data(),
        [&controller]() {
            controller.requestVersion();
        }
    );

    app.add_action(
        cHelpDocActionName.data(),
        [views]() {
            if (views.help) {
                views.help->show();
            }
        }
    );

    app.add_action(
        cHelpAboutActionName.data(),
        [views]() {
            if (views.about) {
                views.about->show();
            }
        }
    );
}
