////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_pulse.h
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
#include <gtkmm/spinbutton.h>
#include <gtkmm/progressbar.h>
#include <model/channel_state.h>
#include <sigc++/sigc++.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class PulseModePage
    /// @brief ModePage implementation for Pulse Mode, inheriting from Gtk::Box.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class PulseModePage : public Gtk::Box {
      public:
        explicit PulseModePage(size_t index);
        virtual ~PulseModePage() override = default;

        PulseModePage(const PulseModePage &) = delete;
        PulseModePage &operator=(const PulseModePage &) = delete;
        PulseModePage(PulseModePage &&) = delete;
        PulseModePage &operator=(PulseModePage &&) = delete;

        void updateState(const ChannelState &state);
        void getState(ChannelState &state) const;
        sigc::signal<void()>& signal_changed() { return m_signalChanged; }

      private:
        void onPulseSpinChanged();
        void onTriggerClicked();

        size_t m_index;
        Gtk::Label m_pulseLabel;
        Gtk::SpinButton m_pulseSpin;
        Gtk::Button m_pulseTriggerBtn;
        Gtk::Label m_descLabel;
        Gtk::ProgressBar m_progressBar;
        mutable bool m_pulseTriggered{false};
        sigc::signal<void()> m_signalChanged;
    };
} // namespace Electux::App::View
