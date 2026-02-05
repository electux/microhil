/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application_slots.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <application.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application menu labels and detailed actions
    ///   cFileLabel - file action label
    ///   cFileQuitLabel - file quit action label
    ///   cFileQuitDetaildAction - file quit detailed action
    ///   cOptionLabel - option action label
    ///   cOptionSettingsLabel - option settings action label
    ///   cOptionSettingsDetaildAction - option settings detailed action
    ///   cHelpLabel - help action label
    ///   cHelpDocLabel - help documentation action label
    ///   cHelpDocDetaildAction - help documentation detailed action
    ///   cHelpAboutLabel - help about action label
    ///   cHelpAboutDetaildAction - help about detailed action
    constexpr std::string_view cFileLabel{"File"}; 
    constexpr std::string_view cFileQuitLabel{"_Quit"};
    constexpr std::string_view cFileQuitDetaildAction{"app.quit"};
    constexpr std::string_view cOptionLabel{"Option"};
    constexpr std::string_view cOptionSettingsLabel{"_Settings"};
    constexpr std::string_view cOptionSettingsDetaildAction{"app.settings"};
    constexpr std::string_view cHelpLabel{"Help"};
    constexpr std::string_view cHelpDocLabel{"_Documentation"};
    constexpr std::string_view cHelpDocDetaildAction{"app.doc"};
    constexpr std::string_view cHelpAboutLabel{"_About"};
    constexpr std::string_view cHelpAboutDetaildAction{"app.about"};
};

using namespace Electux::App;

void EntryApplication::on_startup()
{
    std::cout << "Startup application..." << std::endl;
    Gtk::Application::on_startup();

    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets application menubar
    auto menu = Gio::Menu::create();
    auto submenu_file = Gio::Menu::create();
    submenu_file->append(cFileQuitLabel.data(), cFileQuitDetaildAction.data());
    menu->append_submenu(cFileLabel.data(), submenu_file);
    auto submenu_option = Gio::Menu::create();
    submenu_option->append(cOptionSettingsLabel.data(), cOptionSettingsDetaildAction.data());
    menu->append_submenu(cOptionLabel.data(), submenu_option);
    auto submenu_help = Gio::Menu::create();
    submenu_help->append(cHelpDocLabel.data(), cHelpDocDetaildAction.data());
    submenu_help->append(cHelpAboutLabel.data(), cHelpAboutDetaildAction.data());
    menu->append_submenu(cHelpLabel.data(), submenu_help);
    set_menubar(menu);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Maps signal/slots for application views
    mapping();

    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets AppHome as toplevel window, add to the application window
    add_window(m_home);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Updated settings widgets data based on loaded configuration
    SettingsSetup setup;
    setup.m_controlConfig = m_configManager.getControlConfig();
    setup.m_serialConfig = m_configManager.getSerialConfig();
    setup.m_logConfig = m_configManager.getLogConfig();
    m_settings.setSettingsSetup(setup);
    m_settings.updateUiData();

    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets visibility for AppHome window
    m_home.set_visible(true);
    std::cout << "Startup application done." << std::endl;
}

void EntryApplication::onActionQuit()
{
    std::cout << "Quit application." << std::endl;
    m_home.set_visible(false);
    remove_window(m_home);
    quit();
}

bool EntryApplication::onHandleClose()
{
    onActionQuit();
    return false;
}

void EntryApplication::onActionSettings()
{
    m_settings.show();
}

void EntryApplication::onActionDoc()
{
    m_help.show();
}

void EntryApplication::onActionAbout()
{
    m_about.show();
}

void EntryApplication::onSetupChanged(const SettingsSetup &setup)
{
    m_configManager.setControlConfig(setup.m_controlConfig);
    m_configManager.setSerialConfig(setup.m_serialConfig);
    m_configManager.setLogConfig(setup.m_logConfig);
    m_configManager.store();
}
