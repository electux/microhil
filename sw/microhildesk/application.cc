/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.cc
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
#include <glibmm/miscutils.h>
#include <glibmm/refptr.h>
#include "application.h"

using namespace Electux::App::View;
using namespace Electux::App::View::Settings;
using namespace Electux::App::View::Help;
using namespace Electux::App::View::About;

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application parameters
    ///   application_id - application ID
    constexpr const char application_id[]{"electux.io.microhildesk"};
};

using namespace Electux::App;

EntryApplication::EntryApplication():
    Gtk::Application(application_id),
    m_home{AppHome()},
    m_settings{AppSettings()},
    m_help{AppHelp()},
    m_about{AppAbout()}
{
    Glib::set_application_name(application_id);
}

Glib::RefPtr<EntryApplication> EntryApplication::create()
{
    return Glib::make_refptr_for_instance<EntryApplication>(new EntryApplication());
}

