////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application_map.cc
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

#include <application.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Mapper Parameters
	/// @{
	/// @brief A detailed action name, specifying an action.
	constexpr std::string_view cDetailedActionName{"app.quit"};
	/// @brief An accelerator for the detailed action.
	constexpr std::string_view cKeyboardAccelerator{"<Primary>q"};
	/// @brief File quit action name.
	constexpr std::string_view cFileQuitActionName{"quit"};
	/// @brief Option settings action name.
	constexpr std::string_view cOptionSettingsActionName{"settings"};
	/// @brief Help documentation action name.
	constexpr std::string_view cHelpDocActionName{"doc"};
	/// @brief Help about action name.
	constexpr std::string_view cHelpAboutActionName{"about"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Maps signals and actions for the application views and core logic.
///
/// This method handles the registration of keyboard accelerators, binds
/// application actions to their respective handlers, and establishes
/// connections between view signals (like settings changes) and application slots.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::mapping()
{
	// Sets application accelerator for quit action
	set_accel_for_action(cDetailedActionName.data(), cKeyboardAccelerator.data());

	// Maps application actions to their handlers
	add_action(cFileQuitActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionQuit));
	add_action(cOptionSettingsActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionSettings));
	add_action(cHelpDocActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionDoc));
	add_action(cHelpAboutActionName.data(), sigc::mem_fun(*this, &EntryApplication::onActionAbout));

	// Connects close request signal for AppHome window
	m_home.signal_close_request().connect(sigc::mem_fun(*this, &EntryApplication::onHandleClose), false);

	// Maps application setup signals to their handlers
	m_settings.setupChanged().connect(sigc::mem_fun(*this, &EntryApplication::onSetupChanged));
	m_home.controlChanged().connect(sigc::mem_fun(*this, &EntryApplication::onSetupChanged));
}
