/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * about.cc
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
#include <vector>
#include "about.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application about dialog widgets parameters
    ///   programName - program name
    ///   programVersion - program version
    ///   programCopyright - program copyright
    ///   programComments - program comments
    ///   programLicense - program license
    ///   programWebsite - program website
    ///   programWebsiteLabel - program website label 
    ///   programAuthors - program author
    constexpr const char programName[]{"microhildesk"};
    constexpr const char programVersion[]{"1.0.0"};
    constexpr const char programCopyright[]{"Vladimir Roncevic <elektron.ronca@gmail.com>"};
    constexpr const char programComments[]{"This is microhildesk application."};
    constexpr const char programLicense[]{"GPLv3"};
    constexpr const char programWebsite[]{"https://electux.github.io/microhil"};
    constexpr const char programWebsiteLabel[]{"electux.github.io/microhil"};
    constexpr const char programAuthors[]{"Vladimir Roncevic"};
};

using namespace Electux::App::View::About;

AppAbout::AppAbout()
{
    set_program_name(programName);
    set_version(programVersion);
    set_copyright(programCopyright);
    set_comments(programComments);
    set_license(programLicense);
    set_website(programWebsite);
    set_website_label(programWebsiteLabel);
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back(programAuthors);
    set_authors(list_authors);
    set_hide_on_close(true);
}

