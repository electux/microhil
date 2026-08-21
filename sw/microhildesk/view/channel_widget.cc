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

#include <view/channel_widget.h>
#include <format>

namespace
{
	constexpr std::string_view cHomeEnChannelLabel{"Enable Channel #"};
	constexpr std::string_view cHomeToggleChannelLabel{"Toogle Channel #"};
	constexpr std::string_view cHomeToggleChannelButtonActivate{"Activate"};
	constexpr std::string_view cHomeTimerChannelLabel{"Use timer #"};
	constexpr std::string_view cHomeTimerChannelButtonStart{"Start"};
	constexpr std::string_view cHomeChannelModeOptions[]{"Toogle Active", "Timer Active"};
} // namespace

using namespace Electux::App::View;

ChannelWidget::ChannelWidget(size_t index)
	: Gtk::Box(Gtk::Orientation::VERTICAL, 5)
	, m_index(index)
	, m_enableBtn(std::format("{} {}", cHomeEnChannelLabel.data(), index))
	, m_toggleLabel(std::format("{} {}", cHomeToggleChannelLabel.data(), index))
	, m_timerLabel(std::format("{} {}", cHomeTimerChannelLabel.data(), index))
{
	set_margin(10);

	// Setup Enable Button
	append(m_enableBtn);
	m_enableBtn.signal_toggled().connect(sigc::mem_fun(*this, &ChannelWidget::onEnableToggled));

	// Setup Mode ComboBox
	for (const auto& option : cHomeChannelModeOptions)
	{
		m_modeCombo.append(option.data());
	}
	append(m_modeCombo);
	m_modeCombo.signal_changed().connect(sigc::mem_fun(*this, &ChannelWidget::onModeChanged));

	// Setup Toggle Label and Button
	append(m_toggleLabel);
	m_toggleBtn.set_label(cHomeToggleChannelButtonActivate.data());
	append(m_toggleBtn);
	m_toggleBtn.signal_clicked().connect(sigc::mem_fun(*this, &ChannelWidget::onToggleClicked));

	// Setup Timer Label, SpinButton and Button
	append(m_timerLabel);
	m_timerSpin.set_range(0.0, 3600.0);
	m_timerSpin.set_increments(1.0, 10.0);
	append(m_timerSpin);
	m_timerSpin.signal_value_changed().connect(sigc::mem_fun(*this, &ChannelWidget::onTimerValueChanged));

	m_timerToggleBtn.set_label(cHomeTimerChannelButtonStart.data());
	append(m_timerToggleBtn);
	m_timerToggleBtn.signal_clicked().connect(sigc::mem_fun(*this, &ChannelWidget::onTimerToggleClicked));

	// Setup Progress Bar
	m_progressBar.set_fraction(0.0);
	append(m_progressBar);
}

void ChannelWidget::updateState(const ChannelState &state)
{
	m_blockSignals = true;
	m_enableBtn.set_active(state.enabled);
	m_modeCombo.set_active(state.mode);
	m_toggleBtn.set_active(state.toggle);
	m_timerSpin.set_value(state.timer);
	m_timerToggleBtn.set_active(state.timerEnabled);
	m_blockSignals = false;
}

ChannelState ChannelWidget::getState() const
{
	ChannelState state;
	state.enabled = m_enableBtn.get_active();
	state.mode = m_modeCombo.get_active_row_number();
	state.toggle = m_toggleBtn.get_active();
	state.timer = m_timerSpin.get_value_as_int();
	state.timerEnabled = m_timerToggleBtn.get_active();
	return state;
}

void ChannelWidget::onEnableToggled()
{
	if (!m_blockSignals) { m_signalChanged.emit(); }
}

void ChannelWidget::onModeChanged()
{
	if (!m_blockSignals) { m_signalChanged.emit(); }
}

void ChannelWidget::onToggleClicked()
{
	if (!m_blockSignals) { m_signalChanged.emit(); }
}

void ChannelWidget::onTimerValueChanged()
{
	if (!m_blockSignals) { m_signalChanged.emit(); }
}

void ChannelWidget::onTimerToggleClicked()
{
	if (!m_blockSignals) { m_signalChanged.emit(); }
}
