////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_widget.cc
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
#include <view/channel_widget.h>

namespace {
    constexpr std::string_view cChannelEnableLabel{"Enable Channel #"};
    constexpr std::string_view cChannelToggleLabel{"Toogle Channel #"};
    constexpr std::string_view cChannelToggleBtnActivate{"Activate"};
    constexpr std::string_view cChannelTimerLabel{"Use timer #"};
    constexpr std::string_view cChannelTimerBtnStart{"Start"};
    constexpr std::string_view cChannelModeOptions[]{
        "Toogle Active", "Timer Active"
    };
} // namespace

using namespace Electux::App::View;

ChannelWidget::ChannelWidget(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, 5), m_index(index),
      m_enableBtn(std::format("{} {}", cChannelEnableLabel.data(), index)),
      m_toggleLabel(std::format("{} {}", cChannelToggleLabel.data(), index)),
      m_timerLabel(std::format("{} {}", cChannelTimerLabel.data(), index)) {
    set_margin(10);

    append(m_enableBtn);
    m_enableBtn.signal_toggled().connect(
        sigc::mem_fun(*this, &ChannelWidget::onEnableToggled)
    );
    for (const auto &option : cChannelModeOptions) {
        m_modeCombo.append(option.data());
    }
    m_modeCombo.set_active(0);
    append(m_modeCombo);
    m_modeCombo.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onModeChanged)
    );

    append(m_toggleLabel);
    m_toggleBtn.set_label(cChannelToggleBtnActivate.data());
    append(m_toggleBtn);
    m_toggleBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &ChannelWidget::onToggleClicked)
    );

    append(m_timerLabel);
    m_timerSpin.set_range(0.0, 3600.0);
    m_timerSpin.set_increments(1.0, 10.0);
    append(m_timerSpin);
    m_timerSpin.signal_value_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onTimerValueChanged)
    );

    m_timerToggleBtn.set_label(cChannelTimerBtnStart.data());
    append(m_timerToggleBtn);
    m_timerToggleBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &ChannelWidget::onTimerToggleClicked)
    );

    m_progressBar.set_fraction(0.0);
    append(m_progressBar);

    updateSensitivity();
}

void ChannelWidget::updateSensitivity() {
    bool isEnabled = m_enableBtn.get_active();
    int mode = m_modeCombo.get_active_row_number();

    m_modeCombo.set_sensitive(isEnabled);

    bool isToggleActive = isEnabled && (mode == 0);

    m_toggleLabel.set_sensitive(isToggleActive);
    m_toggleBtn.set_sensitive(isToggleActive);

    bool isTimerActive = isEnabled && (mode == 1);

    m_timerLabel.set_sensitive(isTimerActive);
    m_timerSpin.set_sensitive(isTimerActive);
    m_timerToggleBtn.set_sensitive(isTimerActive);
    m_progressBar.set_sensitive(isTimerActive);
}

void ChannelWidget::updateState(const ChannelState &state) {
    m_blockSignals = true;
    m_enableBtn.set_active(state.enabled);
    m_modeCombo.set_active(state.mode);
    m_toggleBtn.set_active(state.toggle);
    m_timerSpin.set_value(state.timer);
    m_timerToggleBtn.set_active(state.timerEnabled);
    m_blockSignals = false;

    updateSensitivity();
}

ChannelState ChannelWidget::getState() const {
    ChannelState state;
    state.enabled = m_enableBtn.get_active();
    state.mode = m_modeCombo.get_active_row_number();
    state.toggle = m_toggleBtn.get_active();
    state.timer = m_timerSpin.get_value_as_int();
    state.timerEnabled = m_timerToggleBtn.get_active();
    return state;
}

void ChannelWidget::onEnableToggled() {
    updateSensitivity();

    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onModeChanged() {
    updateSensitivity();

    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onToggleClicked() {
    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onTimerValueChanged() {
    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onTimerToggleClicked() {
    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}
