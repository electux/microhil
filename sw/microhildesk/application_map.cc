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
#include <application.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application mapper parameters
    ///   cDetailedActionName - a detailed action name, specifying an action
    ///   cKeyboardAccelerator - an accelerator in the format understood by GTK
    ///   cFileQuitActionName - file quit action name
    ///   cOptionSettingsActionName - option settings action name
    ///   cHelpDocActionName - help documenation action name
    ///   cHelpAboutActionName - help about action name
    constexpr std::string_view cDetailedActionName{"app.quit"};
    constexpr std::string_view cKeyboardAccelerator{"<Primary>q"};
    constexpr std::string_view cFileQuitActionName{"quit"};
    constexpr std::string_view cOptionSettingsActionName{"settings"};
    constexpr std::string_view cHelpDocActionName{"doc"};
    constexpr std::string_view cHelpAboutActionName{"about"};
};

using namespace Electux::App;

void EntryApplication::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Sets application accelerator
    set_accel_for_action(cDetailedActionName.data(), cKeyboardAccelerator.data());

    //////////////////////////////////////////////////////////////////////////
    /// @brief Maps application actions to their handlers
    add_action(cFileQuitActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionQuit));
    add_action(cOptionSettingsActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionSettings));
    add_action(cHelpDocActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionDoc));
    add_action(cHelpAboutActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionAbout));

    //////////////////////////////////////////////////////////////////////////
    /// @brief Connects close request signal for AppHome window
    m_home.signal_close_request().connect(sigc::mem_fun(*this, &EntryApplication::onHandleClose), false);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Maps application setup signal
    m_settings.setupChanged().connect(sigc::mem_fun(*this, &EntryApplication::onSetupChanged));
}
