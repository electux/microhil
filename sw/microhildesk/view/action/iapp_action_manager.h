////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iapp_action_manager.h
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

#include <gtkmm/application.h>
#include <iapp_controller.h>
#include <view/about/iabout_view.h>
#include <view/help/ihelp_view.h>
#include <view/ihome_view.h>
#include <view/settings/isettings_view.h>

namespace Electux::App::View::Action {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @struct AppViewsContext
    /// @brief Group of application views accessed by action handlers.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    struct AppViewsContext {
        IHomeView *home{nullptr};
        Settings::ISettingsView *settings{nullptr};
        Help::IHelpView *help{nullptr};
        About::IAboutView *about{nullptr};
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IAppActionManager
    /// @brief Interface for registering GTK actions and keyboard shortcuts.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IAppActionManager {
      public:
        virtual ~IAppActionManager() = default;

        virtual void registerActions(
            Gtk::Application &app,
            IAppController &controller,
            const AppViewsContext &views
        ) = 0;
    };
} // namespace Electux::App::View::Action
