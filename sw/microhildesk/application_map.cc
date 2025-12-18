/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application_map.cc
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
#include "application.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application mapper parameters
    ///   detailed_action_name - a detailed action name, specifying an action
    ///   keyboard_accelerator - an accelerator in the format understood by GTK
    ///   file_quit_action_name - file quit action name
    ///   option_settings_action_name - option settings action name
    ///   help_doc_action_name - help documenation action name
    ///   help_about_action_name - help about action name
    constexpr const char detailed_action_name[]{"app.quit"};
    constexpr const char keyboard_accelerator[]{"<Primary>q"}; 
    constexpr const char file_quit_action_name[]{"quit"};
    constexpr const char option_settings_action_name[]{"settings"};
    constexpr const char help_doc_action_name[]{"doc"};
    constexpr const char help_about_action_name[]{"about"};
};

using namespace Electux::App;

void EntryApplication::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// Sets a keyboard accelerator that will trigger application quit
    set_accel_for_action(detailed_action_name, keyboard_accelerator);

    //////////////////////////////////////////////////////////////////////////
    /// Maps application actions
    add_action(file_quit_action_name, sigc::mem_fun(*this, &EntryApplication::on_action_quit));
    add_action(option_settings_action_name, sigc::mem_fun(*this, &EntryApplication::on_action_settings));
    add_action(help_doc_action_name, sigc::mem_fun(*this, &EntryApplication::on_action_doc));
    add_action(help_about_action_name, sigc::mem_fun(*this, &EntryApplication::on_action_about));
}
