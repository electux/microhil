/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application_slots.cc
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "application.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application parameters
    ///   file_label - file action label
    ///   file_quit_label - file quit action label
    ///   file_quit_detaild_action - file quit detailed action
    ///   option_label - option action label
    ///   option_settings_label - option settings action label
    ///   option_settings_detaild_action - option settings detailed action
    ///   help_label - help action label
    ///   help_doc_label - help documentation action label
    ///   help_doc_detaild_action - help documentation detailed action
    ///   help_about_label - help about action label
    ///   help_about_detaild_action - help about detailed action
    constexpr const char file_label[]{"File"}; 
    constexpr const char file_quit_label[]{"_Quit"};
    constexpr const char file_quit_detaild_action[]{"app.quit"};
    constexpr const char option_label[]{"Option"};
    constexpr const char option_settings_label[]{"_Settings"};
    constexpr const char option_settings_detaild_action[]{"app.setting"};
    constexpr const char help_label[]{"Help"};
    constexpr const char help_doc_label[]{"_Documentation"};
    constexpr const char help_doc_detaild_action[]{"app.doc"};
    constexpr const char help_about_label[]{"_About"};
    constexpr const char help_about_detaild_action[]{"app.about"};
};

using namespace Electux::App;

void EntryApplication::on_startup()
{
    Gtk::Application::on_startup();

    //////////////////////////////////////////////////////////////////////////
    /// Sets application menubar
    auto menu = Gio::Menu::create();
    auto submenu_file = Gio::Menu::create();
    submenu_file->append(file_quit_label, file_quit_detaild_action);
    menu->append_submenu(file_label, submenu_file);
    auto submenu_option = Gio::Menu::create();
    submenu_option->append(option_settings_label, option_settings_detaild_action);
    menu->append_submenu(option_label, submenu_option);
    auto submenu_help = Gio::Menu::create();
    submenu_help->append(help_doc_label, help_doc_detaild_action);
    submenu_help->append(help_about_label, help_about_detaild_action);
    menu->append_submenu(help_label, submenu_help);
    set_menubar(menu);

    //////////////////////////////////////////////////////////////////////////
    /// Maps application actions and keyboard accelerators
    mapping();

    //////////////////////////////////////////////////////////////////////////
    /// Sets AppHome as toplevel window, add to the application window
    add_window(m_home);

    //////////////////////////////////////////////////////////////////////////
    /// Sets visability for AppHome window
    m_home.set_visible(true);
}

void EntryApplication::on_action_quit()
{
    m_home.set_visible(false);
    remove_window(m_home);
    quit();
}

void EntryApplication::on_action_settings()
{
    m_settings.show();
}

void EntryApplication::on_action_doc()
{
    m_help.show();
}

void EntryApplication::on_action_about()
{
    m_about.show();
}
