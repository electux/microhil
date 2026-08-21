////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.h
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

#include <memory>
#include <config/iconfig.h>
#include <model/imodel.h>
#include <view/settings_setup.h>
#include <iapp_controller.h>

namespace Electux::App::Com { class ICom; class ISerial; }
namespace Electux::App::Logger { class ILog; }

namespace Electux::App
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class AppController
	/// @brief Pure C++ coordination controller managing config loading, storing, and model change propagation.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class AppController : public IAppController
	{
	public:
		AppController();
		virtual ~AppController() override;

		AppController(const AppController &) = delete;
		AppController &operator=(const AppController &) = delete;

		void startup() override;
		void shutdown() override;

		Model::IModel& getModel() override;
		const Model::IModel& getModel() const override;

		void onSetupChanged(const Model::SettingsSetup &setup) override;

	private:
		void configureLogger();
		void configureSerial();

		std::unique_ptr<Config::IConfig> m_configManager;
		std::unique_ptr<Com::ICom> m_comChannel;
		Com::ISerial* m_serialConfig{nullptr};
		std::unique_ptr<Logger::ILog> m_logger;
	};
} // namespace Electux::App
