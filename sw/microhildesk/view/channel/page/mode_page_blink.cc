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
    constexpr std::string_view cBlinkOnLabel{"Blink ON (ms)"};
    constexpr std::string_view cBlinkOffLabel{"Blink OFF (ms)"};
    constexpr std::string_view cBlinkCountLabel{"Count"};
    constexpr std::string_view cBlinkBtnStart{"Start"};
    constexpr std::string_view cBlinkBtnStop{"Stop"};
    constexpr std::string_view cChannelBlinkDesc{"Cycle the channel state ON and OFF."};
    constexpr int cBoxSpacing{5};
    constexpr int cMarginTopBottom{15};
    constexpr double cBlinkTimeMin{10.0};
    constexpr double cBlinkTimeMax{10000.0};
    constexpr double cBlinkTimeStep{10.0};
    constexpr double cBlinkTimePage{100.0};
    constexpr double cBlinkCountMin{0.0};
    constexpr double cBlinkCountMax{1000.0};
    constexpr double cBlinkCountStep{1.0};
    constexpr double cBlinkCountPage{10.0};
} // namespace

using namespace Electux::App::View;

BlinkModePage::BlinkModePage(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, cBoxSpacing),
      m_index(index) {
    m_blinkOnLabel.set_label(cBlinkOnLabel.data());
    m_blinkOffLabel.set_label(cBlinkOffLabel.data());
    m_blinkCountLabel.set_label(cBlinkCountLabel.data());
    m_descLabel.set_label(cChannelBlinkDesc.data());

    append(m_blinkOnLabel);
    m_blinkOnSpin.set_range(cBlinkTimeMin, cBlinkTimeMax);
    m_blinkOnSpin.set_increments(cBlinkTimeStep, cBlinkTimePage);
    append(m_blinkOnSpin);

    append(m_blinkOffLabel);
    m_blinkOffSpin.set_range(cBlinkTimeMin, cBlinkTimeMax);
    m_blinkOffSpin.set_increments(cBlinkTimeStep, cBlinkTimePage);
    append(m_blinkOffSpin);

    append(m_blinkCountLabel);
    m_blinkCountSpin.set_range(cBlinkCountMin, cBlinkCountMax);
    m_blinkCountSpin.set_increments(cBlinkCountStep, cBlinkCountPage);
    append(m_blinkCountSpin);

    m_descLabel.set_wrap(true);
    m_descLabel.set_justify(Gtk::Justification::CENTER);
    m_descLabel.set_margin_top(cMarginTopBottom);
    m_descLabel.set_margin_bottom(cMarginTopBottom);
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
    m_blinkToggleBtn.set_label(
        state.blinkEnabled ? cBlinkBtnStop.data() : cBlinkBtnStart.data()
    );
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
    bool active = m_blinkToggleBtn.get_active();
    m_blinkToggleBtn.set_label(
        active ? cBlinkBtnStop.data() : cBlinkBtnStart.data()
    );
    m_progressBar.set_fraction(active ? 1.0 : 0.0);
    m_signalChanged.emit();
}
