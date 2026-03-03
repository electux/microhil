////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// help.h
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
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <gtkmm/window.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::View::Help
/// @brief Namespace for application help and documentation view components
namespace Electux::App::View::Help
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class AppHelp
	/// @brief Help view window definition for application documentation.
	///
	/// This window provides users with access to local documentation or
	/// help resources related to microhildesk functionality.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class AppHelp : public Gtk::Window
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief AppHelp constructor.
		////////////////////////////////////////////////////////////////////////////////////////////////
		explicit AppHelp();
	};
} // namespace Electux::App::View::Help
