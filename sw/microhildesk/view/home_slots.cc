////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home_slots.cc
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
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string_view>
#include <ranges>
#include <numeric>
#include <view/home.h>
#include <params/channel_params.h>

using namespace Electux::App::View;
using namespace Electux::App::Model;
using namespace Electux::App::Params::Channel;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Signal handler for enablement channel.
/// @param index Index of the affected channel.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::onChannelEnableChanged(size_t index)
{
	if (m_blockSignals) { return; }

	const auto controlEnableKey = m_setup.m_config.toString(ModelControlKey::Enable);
	auto value = boolToString(m_enableChannels[index].get_active());
	update_control_config(controlEnableKey, index, value);
	m_controlSignal.emit(m_setup);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Signal handler for setup channel mode.
/// @param index Index of the affected channel.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::onChannelModeChanged(size_t index)
{
	if (m_blockSignals) { return; }

	const auto controlModeKey = m_setup.m_config.toString(ModelControlKey::Mode);
	auto controlModeComboValue = std::to_string(m_selectControlChannels[index].get_active_row_number());
	update_control_config(controlModeKey, index, controlModeComboValue);
	m_controlSignal.emit(m_setup);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Signal handler for toggle mode.
/// @param index Index of the affected channel.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::onChannelToggleChanged(size_t index)
{
	if (m_blockSignals) { return; }

	const auto controlToggleKey = m_setup.m_config.toString(ModelControlKey::Toggle);
	auto controlToggleButtonValue = boolToString(m_toggleChannels[index].get_active());
	update_control_config(controlToggleKey, index, controlToggleButtonValue);
	m_controlSignal.emit(m_setup);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Signal handler for timer value changes.
/// @param index Index of the affected channel.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::onChannelTimerChanged(size_t index)
{
	if (m_blockSignals) { return; }

	const auto controlTimerKey = m_setup.m_config.toString(ModelControlKey::Timer);
	auto controlTimerSpinValue = std::to_string(m_spinTimerChannels[index].get_value_as_int());
	update_control_config(controlTimerKey, index, controlTimerSpinValue);
	m_controlSignal.emit(m_setup);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Signal handler for timer activation toggle.
/// @param index Index of the affected channel.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::onChannelTimerToggleChanged(size_t index)
{
	if (m_blockSignals) { return; }

	const auto controlTimerEnableKey = m_setup.m_config.toString(ModelControlKey::TimerEnable);
	auto controlTimerEnableButtonValue = boolToString(m_toggleTimerChannels[index].get_active());
	update_control_config(controlTimerEnableKey, index, controlTimerEnableButtonValue);
	m_controlSignal.emit(m_setup);
}
