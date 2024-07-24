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

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application about dialog widgets parameters
    ///   program_name - program name
    ///   program_version - program version
    ///   program_copyright - program copyright
    ///   program_comments - program comments
    ///   program_license - program license
    ///   program_website - program website
    ///   program_website_label - program website label 
    ///   program_authors - program author
    constexpr const char program_name[]{"microhildesk"};
    constexpr const char program_version[]{"1.0.0"};
    constexpr const char program_copyright[]{
        "Vladimir Roncevic <elektron.ronca@gmail.com>"
    };
    constexpr const char program_comments[]{
        "This is microhildesk application."
    };
    constexpr const char program_license[]{"GPLv3"};
    constexpr const char program_website[]{
        "https://electux.github.io/microhil"
    };
    constexpr const char program_website_label[]{
        "electux.github.io/microhil"
    };
    constexpr const char program_authors[]{"Vladimir Roncevic"};
};

using namespace Electux::App::View::About;

AppAbout::AppAbout()
{
    set_program_name(program_name);
    set_version(program_version);
    set_copyright(program_copyright);
    set_comments(program_comments);
    set_license(program_license);
    set_website(program_website);
    set_website_label(program_website_label);
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back(program_authors);
    set_authors(list_authors);
    set_hide_on_close(true);
}

