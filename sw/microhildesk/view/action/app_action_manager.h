////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_action_manager.h
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

#include <view/action/iapp_action_manager.h>

namespace Electux::App::View::Action {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppActionManager
    /// @brief Registers application actions, accelerators, and connects action signals.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppActionManager : public IAppActionManager {
      public:
        AppActionManager() = default;
        ~AppActionManager() override = default;

        AppActionManager(const AppActionManager &) = delete;
        AppActionManager &operator=(const AppActionManager &) = delete;

        void registerActions(
            Gtk::Application &app,
            IAppController &controller,
            const AppViewsContext &views
        ) override;
    };
} // namespace Electux::App::View::Action
