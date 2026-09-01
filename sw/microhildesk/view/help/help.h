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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>
#include <view/help/ihelp_view.h>

namespace Electux::App::View::Help {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppHelp
    /// @brief Help view window definition for application documentation.
    ///
    /// This window provides users with access to local documentation or
    /// help resources related to microhildesk functionality.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppHelp : public Gtk::Window, public IHelpView {
      public:
        explicit AppHelp();
        virtual ~AppHelp() override = default;

        AppHelp(const AppHelp &) = delete;
        AppHelp &operator=(const AppHelp &) = delete;

        void show() override;
        Gtk::Window &getGtkWindow() override;

      private:
        Gtk::Box m_boxMain{Gtk::Orientation::VERTICAL, 10};
        Gtk::ScrolledWindow m_scrolledWindow{};
        Gtk::Box m_boxContent{Gtk::Orientation::VERTICAL, 8};
        Gtk::Label m_labelTitle{};
        Gtk::Label m_labelContent{};
        Gtk::Button m_buttonClose{};
    };
} // namespace Electux::App::View::Help
