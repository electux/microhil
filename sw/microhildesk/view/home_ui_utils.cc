////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home_ui_utils.cc
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

#include <view/home.h>
#include <params/channel_params.h>

using namespace Electux::App::View;
using namespace Electux::App::Model;
using namespace Electux::App::Params::Channel;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Updates UI widgets with data from loaded configuration.
/// Blocks signals during the update to prevent feedback loops.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::updateUiData()
{
	m_blockSignals = true;
	const auto& config = m_setup.m_config;
	const auto controlEnableKey = config.toString(ModelControlKey::Enable);
	const auto controlModeKey = config.toString(ModelControlKey::Mode);
	const auto controlToggleKey = config.toString(ModelControlKey::Toggle);
	const auto controlTimerKey = config.toString(ModelControlKey::Timer);
	const auto controlTimerEnableKey = config.toString(ModelControlKey::TimerEnable);

	for (ssize_t i = 0; i < cNumOfChannels; i++)
	{
		auto controlEnableValue = extract_config(controlEnableKey, i);
		m_enableChannels[i].set_active(controlEnableValue == cTrue);
		
		auto controlModeValue = std::stoi(extract_config(controlModeKey, i));
		m_selectControlChannels[i].set_active(controlModeValue);
		
		auto controlToggleValue = extract_config(controlToggleKey, i);
		m_toggleChannels[i].set_active(controlToggleValue == cTrue);
		
		auto controlTimerValue = std::stoi(extract_config(controlTimerKey, i));
		m_spinTimerChannels[i].set_value(controlTimerValue);
		
		auto controlTimerEnableValue = extract_config(controlTimerEnableKey, i);
		m_toggleTimerChannels[i].set_active(controlTimerEnableValue == cTrue);
	}

	m_blockSignals = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets UI data from widgets and saves them to the configuration model.
/// Emits the controlChanged signal after updating the setup.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::getUiData()
{
	const auto& config = m_setup.m_config;
	const auto controlEnableKey = config.toString(ModelControlKey::Enable);
	const auto controlModeKey = config.toString(ModelControlKey::Mode);
	const auto controlToggleKey = config.toString(ModelControlKey::Toggle);
	const auto controlTimerKey = config.toString(ModelControlKey::Timer);
	const auto controlTimerEnableKey = config.toString(ModelControlKey::TimerEnable);

	for (ssize_t i = 0; i < cNumOfChannels; i++)
	{
		auto controlEnableCheckValue = boolToString(m_enableChannels[i].get_active());
		update_control_config(controlEnableKey, i, controlEnableCheckValue);   
		
		auto controlModeComboValue = std::to_string(m_selectControlChannels[i].get_active_row_number());
		update_control_config(controlModeKey, i, controlModeComboValue);
		
		auto controlToggleButtonValue = boolToString(m_toggleChannels[i].get_active());
		update_control_config(controlToggleKey, i, controlToggleButtonValue);
		
		auto controlTimerSpinValue = std::to_string(m_spinTimerChannels[i].get_value_as_int());
		update_control_config(controlTimerKey, i, controlTimerSpinValue);
		
		auto controlTimerEnableButtonValue = boolToString(m_toggleTimerChannels[i].get_active());
		update_control_config(controlTimerEnableKey, i, controlTimerEnableButtonValue);
	}

	m_controlSignal.emit(m_setup);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Splits input string into vector of substrings.
/// @param input Input string to split.
/// @return Vector of substrings.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> AppHome::split_to_vector(const std::string_view &input)
{
	std::vector<std::string> elements;
	std::stringstream ss{std::string(input)};
	std::string item;

	while (ss >> item)
	{
		elements.push_back(item);
	}

	return elements;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Extracts nth substring from input string.
/// @param input Input string.
/// @param index Index of substring to extract.
/// @return Extracted substring or empty string if index out of bounds.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string AppHome::extract_param_value_by_index(const std::string_view &input, size_t index)
{
	auto elements = split_to_vector(input);

	if (index < elements.size())
	{
		return elements[index];
	}

	return std::string(cEmptyString);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Updates nth substring in input string based on channel parameters.
/// @param input Input string.
/// @param index Index of substring to update.
/// @param newValue New value for the substring.
/// @return The updated string.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string AppHome::update_param_value_by_index(const std::string_view &input, size_t index, const std::string_view &newValue)
{
	auto elements = split_to_vector(input);

	if (elements.size() < cNumOfChannels)
	{
		std::string defaultValue = elements.empty() ? std::string(newValue) : elements.back();
		elements.resize(cNumOfChannels, defaultValue);
	}

	if (index < elements.size())
	{
		elements[index] = std::string(newValue);
	}

	std::string result;
	for (size_t i = 0; i < elements.size(); ++i)
	{
		result += elements[i] + (i < elements.size() - 1 ? std::string(cSpaceString) : "");
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Updates control configuration parameter in the model.
/// @param key Configuration key to update.
/// @param index Index of the parameter to update.
/// @param value New value for the configuration key.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::update_control_config(const std::string_view &key, size_t index, const std::string_view &value)
{
	auto controlEntity = m_setup.m_config.getEntity(key);
	auto controlValue = update_param_value_by_index(controlEntity, index, value);
	m_setup.m_config.update(key, controlValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Extracts control configuration parameter from the model.
/// @param key Configuration key to extract.
/// @param index Index of the parameter to extract.
/// @return Extracted value for the configuration key.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string AppHome::extract_config(const std::string_view &key, size_t index)
{
	auto controlEntity = m_setup.m_config.getEntity(key);
	return extract_param_value_by_index(controlEntity, index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Returns the signal emitted when control settings change.
/// @return The SigSettings signal instance.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SigSettings AppHome::controlChanged()
{
	return m_controlSignal;
}
