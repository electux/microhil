////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_pulse.cc
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
#include <view/channel/mode_page_pulse.h>

namespace {
    constexpr std::string_view cChannelPulseLabel{"Pulse (ms) #"};
    constexpr std::string_view cChannelPulseBtnTrigger{"Trigger"};
} // namespace

using namespace Electux::App::View;

PulseModePage::PulseModePage(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, 5),
      m_index(index) {
    m_pulseLabel.set_label(std::format("{} {}", cChannelPulseLabel.data(), index));
    m_descLabel.set_label("Generate a short momentary pulse.");

    append(m_pulseLabel);

    m_pulseSpin.set_range(10.0, 10000.0);
    m_pulseSpin.set_increments(10.0, 100.0);
    append(m_pulseSpin);

    m_descLabel.set_wrap(true);
    m_descLabel.set_justify(Gtk::Justification::CENTER);
    m_descLabel.set_margin_top(15);
    m_descLabel.set_margin_bottom(15);
    m_descLabel.set_vexpand(true);
    m_descLabel.set_valign(Gtk::Align::END);
    append(m_descLabel);

    m_pulseTriggerBtn.set_label(cChannelPulseBtnTrigger.data());
    append(m_pulseTriggerBtn);

    m_progressBar.set_fraction(0.0);
    append(m_progressBar);

    m_pulseSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &PulseModePage::onPulseSpinChanged)
    );
    m_pulseTriggerBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &PulseModePage::onTriggerClicked)
    );
}

void PulseModePage::updateState(const ChannelState &state) {
    m_pulseSpin.set_value(state.pulseTime);
    m_progressBar.set_fraction(state.pulseTriggered ? 1.0 : 0.0);
}

void PulseModePage::getState(ChannelState &state) const {
    state.pulseTime = m_pulseSpin.get_value_as_int();
    state.pulseTriggered = m_pulseTriggered;
    m_pulseTriggered = false; // Latch mechanism resets flag after read
}

void PulseModePage::onPulseSpinChanged() {
    m_signalChanged.emit();
}

void PulseModePage::onTriggerClicked() {
    m_pulseTriggered = true;
    m_progressBar.set_fraction(1.0);
    m_signalChanged.emit();
}
