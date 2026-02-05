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
#include <application.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application parameters
    ///   cApplicationId - application ID
    constexpr std::string_view cApplicationId{"electux.io.microhildesk"};
};

using namespace Electux::App;

EntryApplication::EntryApplication(): Gtk::Application(cApplicationId.data())
{
    Glib::set_application_name(cApplicationId.data());
}

Glib::RefPtr<EntryApplication> EntryApplication::create()
{
    return Glib::make_refptr_for_instance<EntryApplication>(new EntryApplication());
}

