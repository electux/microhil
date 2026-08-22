////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iapp_controller.h
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

namespace Electux::App
{
	namespace Model
	{
		class IModel;
		class SettingsSetup;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class IAppController
	/// @brief Interface defining the contract for the application business logic coordinator.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class IAppController
	{
	public:
		virtual ~IAppController() = default;

		virtual void startup() = 0;
		virtual void shutdown() = 0;

		virtual const Model::IModel& getModel() const = 0;

		virtual void onSetupChanged(const Model::SettingsSetup &setup) = 0;
	};
} // namespace Electux::App
