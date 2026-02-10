/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home_slots.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <string_view>
#include <ranges>
#include <numeric>
#include <view/home.h>
#include <params/channel_params.h>

namespace {
    /////////////////////////////////////////////////////////////////////
    /// @brief Common string constants and character delimiters
    constexpr std::string_view cEmptyString = "";
    constexpr std::string_view cSpaceString = " ";
    constexpr char cSpaceDelimiter = ' ';

    /////////////////////////////////////////////////////////////////////
    /// @brief String representations for boolean values
    constexpr std::string_view cTrue = "true";
    constexpr std::string_view cFalse = "false";

    /////////////////////////////////////////////////////////////////////
    /// @brief Converts a boolean value to its string representation
    /// @param value Boolean value to convert
    /// @return "true" if value is true, "false" otherwise
    constexpr std::string_view boolToString(bool value)
    {
        return value ? cTrue : cFalse;
    }
}

using namespace Electux::App::View;
using namespace Electux::App::Params::Channel;

void AppHome::updateUiData()
{
    m_blockSignals = true;
    const auto& config = m_setup.m_controlConfig;
    const auto controlEnableKey = config.toString(ModelControl::ModelControlKey::Enable);
    const auto controlModeKey = config.toString(ModelControl::ModelControlKey::Mode);
    const auto controlToggleKey = config.toString(ModelControl::ModelControlKey::Toggle);
    const auto controlTimerKey = config.toString(ModelControl::ModelControlKey::Timer);
    const auto controlTimerEnableKey = config.toString(ModelControl::ModelControlKey::TimerEnable);

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

void AppHome::getUiData()
{
    const auto& config = m_setup.m_controlConfig;
    const auto controlEnableKey = config.toString(ModelControl::ModelControlKey::Enable);
    const auto controlModeKey = config.toString(ModelControl::ModelControlKey::Mode);
    const auto controlToggleKey = config.toString(ModelControl::ModelControlKey::Toggle);
    const auto controlTimerKey = config.toString(ModelControl::ModelControlKey::Timer);
    const auto controlTimerEnableKey = config.toString(ModelControl::ModelControlKey::TimerEnable);

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

void AppHome::onChannelEnableChanged(size_t index)
{
    if (m_blockSignals)
    {
        return;
    }

    const auto controlEnableKey = m_setup.m_controlConfig.toString(ModelControl::ModelControlKey::Enable);
    auto value = boolToString(m_enableChannels[index].get_active());
    update_control_config(controlEnableKey, index, value);
    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelModeChanged(size_t index)
{
    if (m_blockSignals)
    {
        return;
    }

    const auto controlModeKey = m_setup.m_controlConfig.toString(ModelControl::ModelControlKey::Mode);
    auto controlModeComboValue = std::to_string(m_selectControlChannels[index].get_active_row_number());
    update_control_config(controlModeKey, index, controlModeComboValue);
    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelToggleChanged(size_t index)
{
    if (m_blockSignals)
    {
        return;
    }

    const auto controlToggleKey = m_setup.m_controlConfig.toString(ModelControl::ModelControlKey::Toggle);
    auto controlToggleButtonValue = boolToString(m_toggleChannels[index].get_active());
    update_control_config(controlToggleKey, index, controlToggleButtonValue);
    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelTimerChanged(size_t index)
{
    if (m_blockSignals)
    {
        return;
    }

    const auto controlTimerKey = m_setup.m_controlConfig.toString(ModelControl::ModelControlKey::Timer);
    auto controlTimerSpinValue = std::to_string(m_spinTimerChannels[index].get_value_as_int());
    std::cout << "Timer value changed for channel " << index << ": " << controlTimerSpinValue << std::endl;
    update_control_config(controlTimerKey, index, controlTimerSpinValue);
    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelTimerToggleChanged(size_t index)
{
    if (m_blockSignals)
    {
        return;
    }

    const auto controlTimerEnableKey = m_setup.m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable);
    auto controlTimerEnableButtonValue = boolToString(m_toggleTimerChannels[index].get_active());
    update_control_config(controlTimerEnableKey, index, controlTimerEnableButtonValue);
    m_controlSignal.emit(m_setup);
}

SigSettings AppHome::controlChanged()
{
    return m_controlSignal;
}

std::vector<std::string> AppHome::split_to_vector(const std::string_view &input)
{
    std::vector<std::string> elements;
    std::stringstream ss{std::string(input)};
    std::string item;
    while (ss >> item) {
        elements.push_back(item);
    }
    return elements;
}

std::string AppHome::extract_param_value_by_index(const std::string_view &input, size_t index)
{
    auto elements = split_to_vector(input);

    if (index < elements.size())
    {
        return elements[index];
    }

    return std::string(cEmptyString);
}

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

void AppHome::update_control_config(const std::string_view &key, size_t index, const std::string_view &value)
{
    auto controlEntity = m_setup.m_controlConfig.getEntity(key);
    auto controlValue = update_param_value_by_index(controlEntity, index, value);
    m_setup.m_controlConfig.update(key, controlValue);
}

std::string AppHome::extract_config(const std::string_view &key, size_t index)
{
    auto controlEntity = m_setup.m_controlConfig.getEntity(key);
    return extract_param_value_by_index(controlEntity, index);
}
