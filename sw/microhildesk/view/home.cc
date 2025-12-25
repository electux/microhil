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
        std::string channel = std::to_string(i);
        m_boxChannels.emplace_back(Gtk::Orientation::VERTICAL);
        m_enableChannels.emplace_back(std::string(homeEnChannelLabel) + channel);
        m_boxChannels[i].append(m_enableChannels[i]);
        m_selectControlChannels.emplace_back();
        for (const auto& option : homeChannelModeOptions)
        {
            m_selectControlChannels[i].append(option);
        }
        m_boxChannels[i].append(m_selectControlChannels[i]);
        m_labelToggleChannels.emplace_back(homeToggleChannelLabel + channel);
        m_boxChannels[i].append(m_labelToggleChannels[i]);
        m_toggleChannels.emplace_back();
        m_toggleChannels[i].set_label(homeToggleChannelButtonActivate);
        m_boxChannels[i].append(m_toggleChannels[i]);
        m_labelTimerChannels.emplace_back(homeTimerChannelLabel + channel);
        m_boxChannels[i].append(m_labelTimerChannels[i]);
        m_spinTimerChannels.emplace_back();
        m_boxChannels[i].append(m_spinTimerChannels[i]);
        m_toggleTimerChannels.emplace_back();
        m_toggleTimerChannels[i].set_label(homeTimerChannelButtonStart);
        m_boxChannels[i].append(m_toggleTimerChannels[i]);
        m_statusTimerChannels.emplace_back();
        m_statusTimerChannels[i].set_fraction(homeStatusFraction);
        m_boxChannels[i].append(m_statusTimerChannels[i]);
        m_boxChannels[i].set_margin(homeBoxChannelMargin);
        m_boxChannels[i].set_spacing(homeBoxChannelSpacing);
        m_boxRoot.append(m_boxChannels[i]);

        //////////////////////////////////////////////////////////////////////
        /// @brief Maps home (signals and slots)
        mapping(i);
    }
}
