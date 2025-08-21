/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * help.cc
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
    ///   help_title - window title
    ///   help_width - window width
    ///   help_height - window height
    constexpr const char help_title[]{"microhildesk"};
    constexpr int help_width{600};
    constexpr int help_height{400};
};

using namespace Electux::App::View::Help;

AppHelp::AppHelp()
{
    set_title(help_title);
    set_default_size(help_width, help_height);
    set_resizable(false);
    set_hide_on_close(true);
}

