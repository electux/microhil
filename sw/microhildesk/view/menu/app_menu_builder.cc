////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_menu_builder.cc
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
#include <view/menu/app_menu_builder.h>

using namespace Electux::App::View::Menu;

namespace {
    constexpr std::string_view cFileLabel{"File"};
    constexpr std::string_view cFileQuitLabel{"_Quit"};
    constexpr std::string_view cFileQuitDetailedAction{"app.file_quit"};

    constexpr std::string_view cOptionLabel{"Option"};
    constexpr std::string_view cOptionSettingsLabel{"_Settings"};
    constexpr std::string_view cOptionSettingsDetailedAction{"app.option_settings"};

    constexpr std::string_view cDeviceLabel{"Device"};
    constexpr std::string_view cDeviceConnectLabel{"_Connect"};
    constexpr std::string_view cDeviceConnectDetailedAction{"app.device_connect"};
    constexpr std::string_view cDeviceDisconnectLabel{"_Disconnect"};
    constexpr std::string_view cDeviceDisconnectDetailedAction{"app.device_disconnect"};
    constexpr std::string_view cDeviceClearLabel{"_Clear Console"};
    constexpr std::string_view cDeviceClearDetailedAction{"app.console_clear"};

    constexpr std::string_view cCommandLabel{"Command"};
    constexpr std::string_view cCmdAllOnLabel{"_All Channels On"};
    constexpr std::string_view cCmdAllOnDetailedAction{"app.cmd_all_on"};
    constexpr std::string_view cCmdAllOffLabel{"_All Channels Off"};
    constexpr std::string_view cCmdAllOffDetailedAction{"app.cmd_all_off"};
    constexpr std::string_view cCmdAllStatLabel{"_All Status"};
    constexpr std::string_view cCmdAllStatDetailedAction{"app.cmd_all_stat"};
    constexpr std::string_view cCmdSysResetLabel{"_System Reset"};
    constexpr std::string_view cCmdSysResetDetailedAction{"app.cmd_sys_reset"};
    constexpr std::string_view cCmdSysIdLabel{"_Get Board ID"};
    constexpr std::string_view cCmdSysIdDetailedAction{"app.cmd_sys_id"};
    constexpr std::string_view cCmdSysVersionLabel{"_Get Version"};
    constexpr std::string_view cCmdSysVersionDetailedAction{"app.cmd_sys_version"};

    constexpr std::string_view cHelpLabel{"Help"};
    constexpr std::string_view cHelpDocLabel{"_Documentation"};
    constexpr std::string_view cHelpDocDetailedAction{"app.doc"};
    constexpr std::string_view cHelpAboutLabel{"_About"};
    constexpr std::string_view cHelpAboutDetailedAction{"app.about"};
} // namespace

Glib::RefPtr<Gio::Menu> AppMenuBuilder::buildMenu() const {
    auto menu = Gio::Menu::create();

    auto submenuFile = Gio::Menu::create();
    submenuFile->append(cFileQuitLabel.data(), cFileQuitDetailedAction.data());
    menu->append_submenu(cFileLabel.data(), submenuFile);

    auto submenuOption = Gio::Menu::create();
    submenuOption->append(
        cOptionSettingsLabel.data(), cOptionSettingsDetailedAction.data()
    );
    menu->append_submenu(cOptionLabel.data(), submenuOption);

    auto submenuDevice = Gio::Menu::create();
    submenuDevice->append(
        cDeviceConnectLabel.data(), cDeviceConnectDetailedAction.data()
    );
    submenuDevice->append(
        cDeviceDisconnectLabel.data(), cDeviceDisconnectDetailedAction.data()
    );
    submenuDevice->append(
        cDeviceClearLabel.data(), cDeviceClearDetailedAction.data()
    );
    menu->append_submenu(cDeviceLabel.data(), submenuDevice);

    auto submenuCommand = Gio::Menu::create();
    submenuCommand->append(
        cCmdAllOnLabel.data(), cCmdAllOnDetailedAction.data()
    );
    submenuCommand->append(
        cCmdAllOffLabel.data(), cCmdAllOffDetailedAction.data()
    );
    submenuCommand->append(
        cCmdAllStatLabel.data(), cCmdAllStatDetailedAction.data()
    );
    submenuCommand->append(
        cCmdSysResetLabel.data(), cCmdSysResetDetailedAction.data()
    );
    submenuCommand->append(
        cCmdSysIdLabel.data(), cCmdSysIdDetailedAction.data()
    );
    submenuCommand->append(
        cCmdSysVersionLabel.data(), cCmdSysVersionDetailedAction.data()
    );
    menu->append_submenu(cCommandLabel.data(), submenuCommand);

    auto submenuHelp = Gio::Menu::create();
    submenuHelp->append(cHelpDocLabel.data(), cHelpDocDetailedAction.data());
    submenuHelp->append(
        cHelpAboutLabel.data(), cHelpAboutDetailedAction.data()
    );
    menu->append_submenu(cHelpLabel.data(), submenuHelp);

    return menu;
}
