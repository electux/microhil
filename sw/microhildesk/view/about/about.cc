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
#include <view/about/about.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application about dialog widgets parameters
    ///   cProgramName - program name
    ///   cProgramVersion - program version
    ///   cProgramCopyright - program copyright
    ///   cProgramComments - program comments
    ///   cProgramLicense - program license
    ///   cProgramWebsite - program website
    ///   cProgramWebsiteLabel - program website label 
    ///   cProgramAuthors - program author
    constexpr std::string_view cProgramName{"microhildesk"};
    constexpr std::string_view cProgramVersion{"1.0.0"};
    constexpr std::string_view cProgramCopyright{"Vladimir Roncevic <elektron.ronca@gmail.com>"};
    constexpr std::string_view cProgramComments{"This is microhildesk application."};
    constexpr std::string_view cProgramLicense{"GPLv3"};
    constexpr std::string_view cProgramWebsite{"https://electux.github.io/microhil"};
    constexpr std::string_view cProgramWebsiteLabel{"electux.github.io/microhil"};
    constexpr std::string_view cProgramAuthors{"Vladimir Roncevic"};
};

using namespace Electux::App::View::About;

AppAbout::AppAbout()
{
    set_program_name(cProgramName.data());
    set_version(cProgramVersion.data());
    set_copyright(cProgramCopyright.data());
    set_comments(cProgramComments.data());
    set_license(cProgramLicense.data());
    set_website(cProgramWebsite.data());
    set_website_label(cProgramWebsiteLabel.data());
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back(cProgramAuthors.data());
    set_authors(list_authors);
    set_hide_on_close(true);
}

