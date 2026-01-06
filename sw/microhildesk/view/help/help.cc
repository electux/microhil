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
#include "help.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application help window widgets parameters
    ///   helpTitle - window title
    ///   helpWidth - window width
    ///   helpHeight - window height
    constexpr std::string_view helpTitle{"microhildesk"};
    constexpr int helpWidth{600};
    constexpr int helpHeight{400};
};

using namespace Electux::App::View::Help;

AppHelp::AppHelp()
{
    set_title(helpTitle.data());
    set_default_size(helpWidth, helpHeight);
    set_resizable(false);
    set_hide_on_close(true);
}

