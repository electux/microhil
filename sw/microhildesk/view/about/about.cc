/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * about.cc
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
#include "about.h"
#include <vector>

using namespace Electux::App::View::About;

AppAbout::AppAbout()
{
    set_program_name("microhildesk");
    set_version("1.0.0");
    set_copyright("Vladimir Roncevic <elektron.ronca@gmail.com>");
    set_comments("This is microhildesk application.");
    set_license("GPLv3");
    set_website("https://electux.github.io/microhil");
    set_website_label("electux.github.io/microhil");
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Vladimir Roncevic");
    set_authors(list_authors);
    set_hide_on_close(true);
}

