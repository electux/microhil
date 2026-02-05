/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * help.cc
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
#include <view/help/help.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application help window widgets parameters
    ///   cHelpTitle - window title
    ///   cHelpWidth - window width
    ///   cHelpHeight - window height
    constexpr std::string_view cHelpTitle{"microhildesk"};
    constexpr int cHelpWidth{600};
    constexpr int cHelpHeight{400};
};

using namespace Electux::App::View::Help;

AppHelp::AppHelp()
{
    set_title(cHelpTitle.data());
    set_default_size(cHelpWidth, cHelpHeight);
    set_resizable(false);
    set_hide_on_close(true);
}

