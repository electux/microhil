////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_timer.cc
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
#include <format>
#include <view/channel/page/mode_page_timer.h>

namespace {
    constexpr std::string_view cChannelTimerLabel{"Use timer #"};
    constexpr std::string_view cChannelTimerBtnStart{"Start"};
} // namespace

using namespace Electux::App::View;

TimerModePage::TimerModePage(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, 5),
      m_index(index) {
    m_timerLabel.set_label(std::format("{} {}", cChannelTimerLabel.data(), index));
    m_descLabel.set_label("Keep the channel active for a time.");

    append(m_timerLabel);

    m_timerSpin.set_range(0.0, 3600.0);
    m_timerSpin.set_increments(1.0, 10.0);
    append(m_timerSpin);

    m_descLabel.set_wrap(true);
    m_descLabel.set_justify(Gtk::Justification::CENTER);
    m_descLabel.set_margin_top(15);
    m_descLabel.set_margin_bottom(15);
    m_descLabel.set_vexpand(true);
    m_descLabel.set_valign(Gtk::Align::END);
    append(m_descLabel);

    m_timerToggleBtn.set_label(cChannelTimerBtnStart.data());
    append(m_timerToggleBtn);

    m_progressBar.set_fraction(0.0);
    append(m_progressBar);

    m_timerSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &TimerModePage::onTimerValueChanged)
    );
    m_timerToggleBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &TimerModePage::onTimerToggleClicked)
    );
}

void TimerModePage::updateState(const ChannelState &state) {
    m_timerSpin.set_value(state.timer);
    m_timerToggleBtn.set_active(state.timerEnabled);
    m_progressBar.set_fraction(state.timerEnabled ? 1.0 : 0.0);
}

void TimerModePage::getState(ChannelState &state) const {
    state.timer = m_timerSpin.get_value_as_int();
    state.timerEnabled = m_timerToggleBtn.get_active();
}

void TimerModePage::onTimerValueChanged() {
    m_signalChanged.emit();
}

void TimerModePage::onTimerToggleClicked() {
    m_progressBar.set_fraction(m_timerToggleBtn.get_active() ? 1.0 : 0.0);
    m_signalChanged.emit();
}
