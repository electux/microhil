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
    ///   detailedActionName - a detailed action name, specifying an action
    ///   keyboardAccelerator - an accelerator in the format understood by GTK
    ///   fileQuitActionName - file quit action name
    ///   optionSettingsActionName - option settings action name
    ///   helpDocActionName - help documenation action name
    ///   helpAboutActionName - help about action name
    constexpr const char detailedActionName[]{"app.quit"};
    constexpr const char keyboardAccelerator[]{"<Primary>q"}; 
    constexpr const char fileQuitActionName[]{"quit"};
    constexpr const char optionSettingsActionName[]{"settings"};
    constexpr const char helpDocActionName[]{"doc"};
    constexpr const char helpAboutActionName[]{"about"};
};

using namespace Electux::App;

void EntryApplication::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets application accelerator
    set_accel_for_action(detailedActionName, keyboardAccelerator);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Maps application actions to their handlers
    add_action(fileQuitActionName, sigc::mem_fun(*this, &EntryApplication::onActionQuit));
    add_action(optionSettingsActionName, sigc::mem_fun(*this, &EntryApplication::onActionSettings));
    add_action(helpDocActionName, sigc::mem_fun(*this, &EntryApplication::onActionDoc));
    add_action(helpAboutActionName, sigc::mem_fun(*this, &EntryApplication::onActionAbout));
}
