/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application_map.cc
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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

using namespace Electux::App;

void EntryApplication::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// Sets a keyboard accelerator that will trigger application quit
    set_accel_for_action("app.quit", "<Primary>q");

    //////////////////////////////////////////////////////////////////////////
    /// Maps application actions
    add_action(
        "quit", sigc::mem_fun(*this, &EntryApplication::on_action_quit)
    );
    add_action(
        "setting", sigc::mem_fun(*this, &EntryApplication::on_action_settings)
    );
    add_action(
        "doc", sigc::mem_fun(*this, &EntryApplication::on_action_doc)
    );
    add_action(
        "about", sigc::mem_fun(*this, &EntryApplication::on_action_about)
    );
}
