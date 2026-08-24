////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_blink.cc
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
#include <view/channel/page/mode_page_blink.h>

namespace {
    constexpr std::string_view cBlinkOnLabel{"Blink ON (ms) #"};
    constexpr std::string_view cBlinkOffLabel{"Blink OFF (ms) #"};
    constexpr std::string_view cBlinkCountLabel{"Count #"};
    constexpr std::string_view cBlinkBtnStart{"Start Blink"};
} // namespace

using namespace Electux::App::View;

BlinkModePage::BlinkModePage(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, 5),
      m_index(index) {
    m_blinkOnLabel.set_label(std::format("{} {}", cBlinkOnLabel.data(), index));
    m_blinkOffLabel.set_label(std::format("{} {}", cBlinkOffLabel.data(), index));
    m_blinkCountLabel.set_label(std::format("{} {}", cBlinkCountLabel.data(), index));
    m_descLabel.set_label("Cycle the channel state ON and OFF.");

    append(m_blinkOnLabel);
    m_blinkOnSpin.set_range(10.0, 10000.0);
    m_blinkOnSpin.set_increments(10.0, 100.0);
    append(m_blinkOnSpin);

    append(m_blinkOffLabel);
    m_blinkOffSpin.set_range(10.0, 10000.0);
    m_blinkOffSpin.set_increments(10.0, 100.0);
    append(m_blinkOffSpin);

    append(m_blinkCountLabel);
    m_blinkCountSpin.set_range(0.0, 1000.0);
    m_blinkCountSpin.set_increments(1.0, 10.0);
    append(m_blinkCountSpin);

    m_descLabel.set_wrap(true);
    m_descLabel.set_justify(Gtk::Justification::CENTER);
    m_descLabel.set_margin_top(15);
    m_descLabel.set_margin_bottom(15);
    m_descLabel.set_vexpand(true);
    m_descLabel.set_valign(Gtk::Align::END);
    append(m_descLabel);

    m_blinkToggleBtn.set_label(cBlinkBtnStart.data());
    append(m_blinkToggleBtn);

    m_progressBar.set_fraction(0.0);
    append(m_progressBar);

    m_blinkOnSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &BlinkModePage::onSpinValueChanged)
    );
    m_blinkOffSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &BlinkModePage::onSpinValueChanged)
    );
    m_blinkCountSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &BlinkModePage::onSpinValueChanged)
    );
    m_blinkToggleBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &BlinkModePage::onToggleClicked)
    );
}

void BlinkModePage::updateState(const ChannelState &state) {
    m_blinkOnSpin.set_value(state.blinkOnTime);
    m_blinkOffSpin.set_value(state.blinkOffTime);
    m_blinkCountSpin.set_value(state.blinkCount);
    m_blinkToggleBtn.set_active(state.blinkEnabled);
    m_progressBar.set_fraction(state.blinkEnabled ? 1.0 : 0.0);
}

void BlinkModePage::getState(ChannelState &state) const {
    state.blinkOnTime = m_blinkOnSpin.get_value_as_int();
    state.blinkOffTime = m_blinkOffSpin.get_value_as_int();
    state.blinkCount = m_blinkCountSpin.get_value_as_int();
    state.blinkEnabled = m_blinkToggleBtn.get_active();
}

void BlinkModePage::onSpinValueChanged() {
    m_signalChanged.emit();
}

void BlinkModePage::onToggleClicked() {
    m_progressBar.set_fraction(m_blinkToggleBtn.get_active() ? 1.0 : 0.0);
    m_signalChanged.emit();
}
