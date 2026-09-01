////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iapp_menu_builder.h
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <giomm/menu.h>
#include <glibmm/refptr.h>

namespace Electux::App::View::Menu {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IAppMenuBuilder
    /// @brief Interface for constructing application menubars.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IAppMenuBuilder {
      public:
        virtual ~IAppMenuBuilder() = default;

        virtual Glib::RefPtr<Gio::Menu> buildMenu() const = 0;
    };
} // namespace Electux::App::View::Menu
