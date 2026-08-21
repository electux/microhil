////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application.cc
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

#include <iostream>
#include <string_view>
#include <glibmm/miscutils.h>
#include <glibmm/refptr.h>
#include <application.h>
#include <iapp_controller.h>
#include <app_controller.h>
#include <model/model.h>
#include <view/home.h>
#include <view/settings/settings.h>
#include <view/help/help.h>
#include <view/about/about.h>
#include <view/settings_setup.h>
#include <view/ihome_view.h>
#include <view/settings/isettings_view.h>
#include <view/help/ihelp_view.h>
#include <view/about/iabout_view.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Internal Constants
	/// @{
	constexpr std::string_view cApplicationId{"electux.io.microhildesk"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Mapper Parameters
	/// @{
	constexpr std::string_view cDetailedActionName{"app.quit"};
	constexpr std::string_view cKeyboardAccelerator{"<Primary>q"};
	constexpr std::string_view cFileQuitActionName{"quit"};
	constexpr std::string_view cOptionSettingsActionName{"settings"};
	constexpr std::string_view cHelpDocActionName{"doc"};
	constexpr std::string_view cHelpAboutActionName{"about"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

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

EntryApplication::EntryApplication()
	: Gtk::Application(cApplicationId.data())
	, m_controller(std::make_unique<AppController>())
	, m_home(std::make_unique<View::AppHome>())
	, m_settings(std::make_unique<View::Settings::AppSettings>())
	, m_help(std::make_unique<View::Help::AppHelp>())
	, m_about(std::make_unique<View::About::AppAbout>())
{
	Glib::set_application_name(cApplicationId.data());
}

EntryApplication::~EntryApplication() = default;

Glib::RefPtr<EntryApplication> EntryApplication::create()
{
	return Glib::make_refptr_for_instance<EntryApplication>(new EntryApplication());
}

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
	m_home->connect_close_request(sigc::mem_fun(*this, &EntryApplication::onHandleClose));

	// Maps application setup signals to their handlers
	m_settings->setupChanged().connect(sigc::mem_fun(*this, &EntryApplication::onSetupChanged));
	m_home->controlChanged().connect(sigc::mem_fun(*this, &EntryApplication::onSetupChanged));
}

void EntryApplication::on_startup()
{
	std::cout << "Startup application..." << std::endl;
	Gtk::Application::on_startup();

	// Initialize configuration manager via controller
	m_controller->startup();

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
	add_window(m_home->getGtkWindow());

	// Reactive model changes synchronization (Observer Pattern)
	m_controller->getModel().signal_changed().connect(
		[this]() {
			SettingsSetup setup;
			setup.m_config = m_controller->getModel().clone();
			m_settings->setSettingsSetup(setup);
			m_settings->updateUiData();
			m_home->setControlSetup(setup);
			m_home->updateUiData();
		}
	);

	// Initial data sync
	SettingsSetup setup;
	setup.m_config = m_controller->getModel().clone();
	m_settings->setSettingsSetup(setup);
	m_settings->updateUiData();
	m_home->setControlSetup(setup);
	m_home->updateUiData();

	std::cout << "Startup application done." << std::endl;
}

void EntryApplication::on_activate()
{
	std::cout << "Activate application..." << std::endl;
	Gtk::Application::on_activate();

	// Sets visibility for AppHome window
	m_home->show();

	std::cout << "Activate application done." << std::endl;
}

void EntryApplication::on_shutdown()
{
	std::cout << "Shutting down application..." << std::endl;
	m_controller->shutdown();
	Gtk::Application::on_shutdown();
}

void EntryApplication::onActionQuit()
{
	std::cout << "Quit application." << std::endl;
	m_home->hide();
	remove_window(m_home->getGtkWindow());
	quit();
}

bool EntryApplication::onHandleClose()
{
	onActionQuit();
	return false;
}

void EntryApplication::onActionSettings()
{
	m_settings->show();
}

void EntryApplication::onActionDoc()
{
	m_help->show();
}

void EntryApplication::onActionAbout()
{
	m_about->show();
}

void EntryApplication::onSetupChanged(const SettingsSetup &setup)
{
	m_controller->onSetupChanged(setup);
}
