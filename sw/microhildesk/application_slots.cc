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
#include "application.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application menu labels and detailed actions
    ///   fileLabel - file action label
    ///   fileQuitLabel - file quit action label
    ///   fileQuitDetaildAction - file quit detailed action
    ///   optionLabel - option action label
    ///   optionSettingsLabel - option settings action label
    ///   optionSettingsDetaildAction - option settings detailed action
    ///   helpLabel - help action label
    ///   helpDocLabel - help documentation action label
    ///   helpDocDetaildAction - help documentation detailed action
    ///   helpAboutLabel - help about action label
    ///   helpAboutDetaildAction - help about detailed action
    constexpr const char fileLabel[]{"File"}; 
    constexpr const char fileQuitLabel[]{"_Quit"};
    constexpr const char fileQuitDetaildAction[]{"app.quit"};
    constexpr const char optionLabel[]{"Option"};
    constexpr const char optionSettingsLabel[]{"_Settings"};
    constexpr const char optionSettingsDetaildAction[]{"app.settings"};
    constexpr const char helpLabel[]{"Help"};
    constexpr const char helpDocLabel[]{"_Documentation"};
    constexpr const char helpDocDetaildAction[]{"app.doc"};
    constexpr const char helpAboutLabel[]{"_About"};
    constexpr const char helpAboutDetaildAction[]{"app.about"};
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
    submenu_file->append(fileQuitLabel, fileQuitDetaildAction);
    menu->append_submenu(fileLabel, submenu_file);
    auto submenu_option = Gio::Menu::create();
    submenu_option->append(optionSettingsLabel, optionSettingsDetaildAction);
    menu->append_submenu(optionLabel, submenu_option);
    auto submenu_help = Gio::Menu::create();
    submenu_help->append(helpDocLabel, helpDocDetaildAction);
    submenu_help->append(helpAboutLabel, helpAboutDetaildAction);
    menu->append_submenu(helpLabel, submenu_help);
    set_menubar(menu);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Maps signal/slots for application views
    mapping();

    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets AppHome as toplevel window, add to the application window
    add_window(m_home);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Connects close request signal for AppHome window
    m_home.signal_close_request().connect(sigc::mem_fun(*this, &EntryApplication::onHandleClose), false);

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
