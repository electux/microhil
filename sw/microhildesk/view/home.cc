/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home.cc
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
#include <string>
#include <format>
#include "home.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application home window widgets parameters
    ///   homeTitle - home window title
    ///   homeWidth - home window width
    ///   homeHeight - home window height
    ///   homeNumChannels - number of channels
    ///   homeEnChannelLabel - checkbox enable channel label
    ///   homeToggleChannelLabel - label for toogle channel
    ///   homeToggleChannelButtonActivate - toggle button channel label 
    ///   homeToggleChannelButtonDeactivate - toggle button channel label
    ///   homeTimerChannelLabel - label for timer channel
    ///   homeTimerChannelButtonStart - spinner channel button label
    ///   homeTimerChannelButtonStop - spinner channel button label
    ///   homeStatusFraction - status init fraction
    ///   homeBoxChannelMargin - box channel margin
    ///   homeBoxChannelSpacing - box channel spacing
    ///   homeChannelModeOptions - channel mode options for combobox
    constexpr const char homeTitle[]{"microhildesk"};
    constexpr int homeWidth{600};
    constexpr int homeHeight{250};
    constexpr int homeNumChannels{8};
    constexpr const char homeEnChannelLabel[]{"Enable Channel #"};
    constexpr const char homeToggleChannelLabel[]{"Toogle Channel #"};
    constexpr const char homeToggleChannelButtonActivate[]{"Activate"};
    constexpr const char homeToggleChannelButtonDeactivate[]{"Deactivate"};
    constexpr const char homeTimerChannelLabel[]{"Use timer #"};
    constexpr const char homeTimerChannelButtonStart[]{"Start"};
    constexpr const char homeTimerChannelButtonStop[]{"Stop"};
    constexpr float homeStatusFraction{0.0};
    constexpr int homeBoxChannelMargin{10};
    constexpr int homeBoxChannelSpacing{5};
    constexpr const char *homeChannelModeOptions[]{"Toogle Active", "Timer Active"};
};

using namespace Electux::App::View;

AppHome::AppHome()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup application home window
    set_title(homeTitle);
    set_default_size(homeWidth, homeHeight);
    set_resizable(false);
    set_show_menubar(true);
    m_boxRoot.set_orientation(Gtk::Orientation::HORIZONTAL);
    set_child(m_boxRoot);

    for(auto i = 0; i < homeNumChannels; i++)
    {
        m_boxChannels.emplace_back(Gtk::Orientation::VERTICAL);
        auto& currentBox = m_boxChannels.back();
        m_enableChannels.emplace_back(std::format("{} {}", homeEnChannelLabel, i));
        currentBox.append(m_enableChannels.back());
        m_selectControlChannels.emplace_back();
        for (const auto& option : homeChannelModeOptions)
        {
            m_selectControlChannels.back().append(option);
        }
        currentBox.append(m_selectControlChannels.back());
        m_labelToggleChannels.emplace_back(std::format("{} {}", homeToggleChannelLabel, i));
        currentBox.append(m_labelToggleChannels.back());
        m_toggleChannels.emplace_back();
        m_toggleChannels.back().set_label(homeToggleChannelButtonActivate);
        currentBox.append(m_toggleChannels.back());
        m_labelTimerChannels.emplace_back(std::format("{} {}", homeTimerChannelLabel, i));
        currentBox.append(m_labelTimerChannels.back());
        m_spinTimerChannels.emplace_back();
        currentBox.append(m_spinTimerChannels.back());
        m_toggleTimerChannels.emplace_back();
        m_toggleTimerChannels.back().set_label(homeTimerChannelButtonStart);
        currentBox.append(m_toggleTimerChannels.back());
        m_statusTimerChannels.emplace_back();
        m_statusTimerChannels.back().set_fraction(homeStatusFraction);
        currentBox.append(m_statusTimerChannels.back());
        currentBox.set_margin(homeBoxChannelMargin);
        currentBox.set_spacing(homeBoxChannelSpacing);
        m_boxRoot.append(currentBox);
        mapping(i);
    }
}
