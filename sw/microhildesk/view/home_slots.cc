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
    const auto& config = m_controlSetup.m_controlConfig;
    const auto controlEnableKey = config.toString(ModelControl::ModelControlKey::Enable);
    const auto controlModeKey = config.toString(ModelControl::ModelControlKey::Mode);
    const auto controlToggleKey = config.toString(ModelControl::ModelControlKey::Toggle);
    const auto controlTimerKey = config.toString(ModelControl::ModelControlKey::Timer);
    const auto controlTimerEnableKey = config.toString(ModelControl::ModelControlKey::TimerEnable);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlEnableValue = extract_config(controlEnableKey, i);
        m_enableChannels[i].set_active(controlEnableValue == std::string(cTrue));
        auto controlModeValue = std::stoi(extract_config(controlModeKey, i));
        m_selectControlChannels[i].set_active(controlModeValue);
        auto controlToggleValue = extract_config(controlToggleKey, i);
        m_toggleChannels[i].set_active(controlToggleValue == std::string(cTrue));
        auto controlTimerValue = std::stoi(extract_config(controlTimerKey, i));
        m_spinTimerChannels[i].set_value(controlTimerValue);
        auto controlTimerEnableValue = extract_config(controlTimerEnableKey, i);
        m_toggleTimerChannels[i].set_active(controlTimerEnableValue == std::string(cTrue));
    }
}

void AppHome::getUiData()
{
    const auto& config = m_controlSetup.m_controlConfig;
    const auto controlEnableKey = config.toString(ModelControl::ModelControlKey::Enable);
    const auto controlModeKey = config.toString(ModelControl::ModelControlKey::Mode);
    const auto controlToggleKey = config.toString(ModelControl::ModelControlKey::Toggle);
    const auto controlTimerKey = config.toString(ModelControl::ModelControlKey::Timer);
    const auto controlTimerEnableKey = config.toString(ModelControl::ModelControlKey::TimerEnable);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
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
}

void AppHome::onChannelEnableChanged()
{
    const auto controlEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Enable);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlEnableCheckValue = boolToString(m_enableChannels[i].get_active());
        update_control_config(controlEnableKey, i, controlEnableCheckValue);
    }
}

void AppHome::onChannelModeChanged()
{
    const auto controlModeKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Mode);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlModeComboValue = std::to_string(m_selectControlChannels[i].get_active_row_number());
        update_control_config(controlModeKey, i, controlModeComboValue);
    }
}

void AppHome::onChannelToggleChanged()
{
    const auto controlToggleKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Toggle);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlToggleButtonValue = boolToString(m_toggleChannels[i].get_active());
        update_control_config(controlToggleKey, i, controlToggleButtonValue);
    }
}

void AppHome::onChannelTimerChanged()
{
    const auto controlTimerKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Timer);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlTimerSpinValue = std::to_string(m_spinTimerChannels[i].get_value_as_int());
        update_control_config(controlTimerKey, i, controlTimerSpinValue);
    }
}

void AppHome::onChannelTimerToogleChanged()
{
    const auto controlTimerEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable);

    for (unsigned int i = 0; i < cNumOfChannels; i++)
    {
        auto controlTimerEnableButtonValue = boolToString(m_toggleTimerChannels[i].get_active());
        update_control_config(controlTimerEnableKey, i, controlTimerEnableButtonValue);
    }
}

SigSettings AppHome::controlChanged()
{
    return m_controlSignal;
}

std::string AppHome::extract_param_value_by_index(const std::string_view &input, size_t index)
{
    auto words = input | std::views::split(cSpaceDelimiter) | std::views::transform(
        [](auto &&rng)
        {
            return std::string_view(&*rng.begin(), std::ranges::distance(rng));
        }
    );

    auto it = words.begin();
    for (size_t i = 0; i < index && it != words.end(); ++i)
    {
        ++it;
    }

    return (it != words.end()) ? std::string(*it) : std::string(cEmptyString);
}

std::string AppHome::update_param_value_by_index(const std::string_view &input, size_t index, const std::string_view &newValue)
{
    auto view = input | std::views::split(cSpaceDelimiter) | std::views::transform(
        [](auto &&range)
        {
            return std::string(range.begin(), range.end());
        }
    );

    std::vector<std::string> words{view.begin(), view.end()};

    if (index < words.size())
    {
        words[index] = newValue;
    }

    if (words.empty())
    {
        return std::string(cEmptyString);
    }

    return std::accumulate(
        std::next(words.begin()),
        words.end(),
        words[0],
        [](std::string a, std::string b)
        {
            return std::move(a) + std::string(cSpaceString) + b;
        }
    );
}

void AppHome::update_control_config(const std::string_view &key, size_t index, const std::string_view &value)
{
    auto controlEntity = m_controlSetup.m_controlConfig.getEntity(key);
    auto controlValue = update_param_value_by_index(controlEntity, index, value);
    m_controlSetup.m_controlConfig.update(key, controlValue);
}

std::string AppHome::extract_config(const std::string_view &key, size_t index)
{
    auto controlEntity = m_controlSetup.m_controlConfig.getEntity(key);
    return extract_param_value_by_index(controlEntity, index);
}
