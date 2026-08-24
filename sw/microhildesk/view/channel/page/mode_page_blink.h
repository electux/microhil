////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_blink.h
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
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/progressbar.h>
#include <model/channel_state.h>
#include <sigc++/sigc++.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BlinkModePage
    /// @brief ModePage implementation for Blink Mode, inheriting from Gtk::Box.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BlinkModePage : public Gtk::Box {
      public:
        explicit BlinkModePage(size_t index);
        virtual ~BlinkModePage() override = default;

        BlinkModePage(const BlinkModePage &) = delete;
        BlinkModePage &operator=(const BlinkModePage &) = delete;
        BlinkModePage(BlinkModePage &&) = delete;
        BlinkModePage &operator=(BlinkModePage &&) = delete;

        void updateState(const ChannelState &state);
        void getState(ChannelState &state) const;
        sigc::signal<void()>& signal_changed() { return m_signalChanged; }

      private:
        void onSpinValueChanged();
        void onToggleClicked();

        size_t m_index;
        Gtk::Label m_blinkOnLabel;
        Gtk::SpinButton m_blinkOnSpin;

        Gtk::Label m_blinkOffLabel;
        Gtk::SpinButton m_blinkOffSpin;

        Gtk::Label m_blinkCountLabel;
        Gtk::SpinButton m_blinkCountSpin;

        Gtk::ToggleButton m_blinkToggleBtn;
        Gtk::Label m_descLabel;
        Gtk::ProgressBar m_progressBar;
        sigc::signal<void()> m_signalChanged;
    };
} // namespace Electux::App::View
