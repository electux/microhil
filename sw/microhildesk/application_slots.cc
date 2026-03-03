////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application_slots.cc
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

#include <iostream>
#include <application.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Menu Labels and Actions
	/// @{
	constexpr std::string_view cFileLabel{"File"}; 
	constexpr std::string_view cFileQuitLabel{"_Quit"};
	constexpr std::string_view cFileQuitDetailedAction{"app.quit"};
	constexpr std::string_view cOptionLabel{"Option"};
	constexpr std::string_view cOptionSettingsLabel{"_Settings"};
	constexpr std::string_view cOptionSettingsDetailedAction{"app.settings"};
	constexpr std::string_view cHelpLabel{"Help"};
	constexpr std::string_view cHelpDocLabel{"_Documentation"};
	constexpr std::string_view cHelpDocDetailedAction{"app.doc"};
	constexpr std::string_view cHelpAboutLabel{"_About"};
	constexpr std::string_view cHelpAboutDetailedAction{"app.about"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Handler for the startup signal to initialize application.
/// 
/// Sets up the application menubar, maps signals/slots, adds the main window,
/// and synchronizes UI data with the loaded configuration.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::on_startup()
{
	std::cout << "Startup application..." << std::endl;
	Gtk::Application::on_startup();

	// Initialize configuration manager (load files, create defaults if needed)
	m_configManager->init();

	// Sets application menubar with File, Option and Help menu
	auto menu = Gio::Menu::create();
	auto submenu_file = Gio::Menu::create();
	submenu_file->append(cFileQuitLabel.data(), cFileQuitDetailedAction.data());
	menu->append_submenu(cFileLabel.data(), submenu_file);

	auto submenu_option = Gio::Menu::create();
	submenu_option->append(cOptionSettingsLabel.data(), cOptionSettingsDetailedAction.data());
	menu->append_submenu(cOptionLabel.data(), submenu_option);

	auto submenu_help = Gio::Menu::create();
	submenu_help->append(cHelpDocLabel.data(), cHelpDocDetailedAction.data());
	submenu_help->append(cHelpAboutLabel.data(), cHelpAboutDetailedAction.data());
	menu->append_submenu(cHelpLabel.data(), submenu_help);
	set_menubar(menu);

	// Maps signal/slots for application views and actions
	mapping();

	// Sets AppHome as toplevel window, add to the application window
	add_window(m_home);

	// Updated settings widgets data based on loaded configuration
	SettingsSetup setup;
	setup.m_config = m_configManager->getConfig();
	m_settings.setSettingsSetup(setup);
	m_settings.updateUiData();
	m_home.setControlSetup(setup);
	m_home.updateUiData();

	std::cout << "Startup application done." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Handler for the activate signal to show main application.
/// Sets the visibility of the home window to true.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::on_activate()
{
	std::cout << "Activate application..." << std::endl;
	Gtk::Application::on_activate();

	// Sets visibility for AppHome window
	m_home.set_visible(true);

	std::cout << "Activate application done." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Handler for the shutdown signal to perform cleanup.
/// Stores current configuration to disk before closing.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::on_shutdown()
{
	std::cout << "Shutting down application..." << std::endl;
	m_configManager->store();
	Gtk::Application::on_shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief On action for quit application.
/// Hides the main window, removes it from management, and quits the loop.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::onActionQuit()
{
	std::cout << "Quit application." << std::endl;
	m_home.set_visible(false);
	remove_window(m_home);
	quit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Slot to handle closing the main window.
/// @return Always false to allow the standard signal handling flow.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EntryApplication::onHandleClose()
{
	onActionQuit();
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the application settings window.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::onActionSettings()
{
	m_settings.show();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the help/documentation window.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::onActionDoc()
{
	m_help.show();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the about application dialog.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::onActionAbout()
{
	m_about.show();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Slot to handle setup signal changes from the settings window.
/// @param setup The new settings parameters to be saved.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void EntryApplication::onSetupChanged(const SettingsSetup &setup)
{
	m_configManager->setConfig(setup.m_config);
	m_configManager->store();
}
