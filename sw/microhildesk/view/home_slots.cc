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
#include "home.h"
#include "../params/channel_params.h"

using namespace Electux::App::View;
using namespace Electux::App::Params::Channel;

void AppHome::updateUiData()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Enable);
        auto controlEnableValue = extract_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlEnableKey), i);
        m_enableChannels[i].set_active(controlEnableValue == "true");
        auto controlModeKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Mode);
        auto controlModeValue = std::stoi(extract_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlModeKey).data(), i));
        m_selectControlChannels[i].set_active(controlModeValue);
        auto controlToggleKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Toggle);
        auto controlToggleValue = extract_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlToggleKey), i);
        m_toggleChannels[i].set_active(controlToggleValue == "true");
        auto controlTimerKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Timer);
        auto controlTimerValue = std::stoi(extract_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerKey), i));
        m_spinTimerChannels[i].set_value(controlTimerValue);
        auto controlTimerEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable);
        auto controlTimerEnableValue = extract_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerEnableKey), i);
        m_toggleTimerChannels[i].set_active(controlTimerEnableValue == "true");
    }
}

void AppHome::getUiData()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Enable);
        auto controlEnableCheckValue = m_enableChannels[i].get_active() ? "true" : "false";
        auto controlEnableValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlEnableKey), i, controlEnableCheckValue);
        m_controlSetup.m_controlConfig.update(controlEnableKey, controlEnableValue);
        auto controlModeKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Mode);
        auto controlModeComboValue = m_selectControlChannels[i].get_active_row_number();
        auto controlModeValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlModeKey), i, std::to_string(controlModeComboValue));
        m_controlSetup.m_controlConfig.update(controlModeKey, controlModeValue);
        auto controlToggleKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Toggle);
        auto controlToggleButtonValue = m_toggleChannels[i].get_active() ? "true" : "false";
        auto controlToggleValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlToggleKey), i, controlToggleButtonValue);
        m_controlSetup.m_controlConfig.update(controlToggleKey, controlToggleValue);
        auto controlTimerKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Timer);
        auto controlTimerSpinValue = m_spinTimerChannels[i].get_value_as_int();
        auto controlTimerValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerKey), i, std::to_string(controlTimerSpinValue));
        m_controlSetup.m_controlConfig.update(controlTimerKey, controlTimerValue);
        auto controlTimerEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable);
        auto controlTimerEnableButtonValue = m_toggleTimerChannels[i].get_active() ? "true" : "false";
        auto controlTimerEnableValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerEnableKey), i, controlTimerEnableButtonValue);
        m_controlSetup.m_controlConfig.update(controlTimerEnableKey, controlTimerEnableValue);
    }
}

void AppHome::onChannelEnableChanged()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Enable);
        auto controlEnableCheckValue = m_enableChannels[i].get_active() ? "true" : "false";
        auto controlEnableValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlEnableKey), i, controlEnableCheckValue);
        m_controlSetup.m_controlConfig.update(controlEnableKey, controlEnableValue);
    }
}

void AppHome::onChannelModeChanged()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlModeKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Mode);
        auto controlModeComboValue = m_selectControlChannels[i].get_active_row_number();
        auto controlModeValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlModeKey), i, std::to_string(controlModeComboValue));
        m_controlSetup.m_controlConfig.update(controlModeKey, controlModeValue);
    }
}

void AppHome::onChannelToggleChanged()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlToggleKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Toggle);
        auto controlToggleButtonValue = m_toggleChannels[i].get_active() ? "true" : "false";
        auto controlToggleValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlToggleKey), i, controlToggleButtonValue);
        m_controlSetup.m_controlConfig.update(controlToggleKey, controlToggleValue);
    }
}

void AppHome::onChannelTimerChanged()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlTimerKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::Timer);
        auto controlTimerSpinValue = m_spinTimerChannels[i].get_value_as_int();
        auto controlTimerValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerKey), i, std::to_string(controlTimerSpinValue));
        m_controlSetup.m_controlConfig.update(controlTimerKey, controlTimerValue);
    }
}

void AppHome::onChannelTimerToogleChanged()
{
    for (unsigned int i = 0; i < numOfChannels; i++)
    {
        auto controlTimerEnableKey = m_controlSetup.m_controlConfig.toString(ModelControl::ModelControlKey::TimerEnable);
        auto controlTimerEnableButtonValue = m_toggleTimerChannels[i].get_active() ? "true" : "false";
        auto controlTimerEnableValue = update_param_value_by_index(m_controlSetup.m_controlConfig.getEntity(controlTimerEnableKey), i, controlTimerEnableButtonValue);
        m_controlSetup.m_controlConfig.update(controlTimerEnableKey, controlTimerEnableValue);
    }
}

SigSettings AppHome::controlChanged()
{
    return m_controlSignal;
}

std::string AppHome::extract_param_value_by_index(const std::string &input, size_t index)
{
    auto words = input | std::views::split(' ') | std::views::transform(
        [](auto &&rng) {return std::string_view(&*rng.begin(), std::ranges::distance(rng));}
    );

    auto it = words.begin();
    for (size_t i = 0; i < index && it != words.end(); ++i)
    {
        ++it;
    }

    return (it != words.end()) ? std::string(*it) : "";
}

std::string AppHome::update_param_value_by_index(const std::string &input, size_t index, const std::string &newValue)
{
    auto view = input | std::views::split(' ') | std::views::transform(
        [](auto &&range) {return std::string(range.begin(), range.end());}
    );

    std::vector<std::string> words{view.begin(), view.end()};

    if (index < words.size())
    {
        words[index] = newValue;
    }

    if (words.empty())
    {
        return "";
    }

    return std::accumulate(
        std::next(words.begin()),
        words.end(),
        words[0],
        [](std::string a, std::string b)
        {
            return std::move(a) + " " + b;
        }
    );
}
