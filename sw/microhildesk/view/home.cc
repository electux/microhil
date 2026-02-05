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
#include <view/home.h>
#include <params/channel_params.h>

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application home window widgets parameters
    ///   cHomeTitle - home window title
    ///   cHomeWidth - home window width
    ///   cHomeHeight - home window height
    ///   cHomeEnChannelLabel - checkbox enable channel label
    ///   cHomeToggleChannelLabel - label for toogle channel
    ///   cHomeToggleChannelButtonActivate - toggle button channel label 
    ///   cHomeToggleChannelButtonDeactivate - toggle button channel label
    ///   cHomeTimerChannelLabel - label for timer channel
    ///   cHomeTimerChannelButtonStart - spinner channel button label
    ///   cHomeTimerChannelButtonStop - spinner channel button label
    ///   cHomeStatusFraction - status init fraction
    ///   cHomeBoxChannelMargin - box channel margin
    ///   cHomeBoxChannelSpacing - box channel spacing
    ///   cHomeChannelModeOptions - channel mode options for combobox
    constexpr std::string_view cHomeTitle{"microhildesk"};
    constexpr int cHomeWidth{600};
    constexpr int cHomeHeight{250};
    constexpr std::string_view cHomeEnChannelLabel{"Enable Channel #"};
    constexpr std::string_view cHomeToggleChannelLabel{"Toogle Channel #"};
    constexpr std::string_view cHomeToggleChannelButtonActivate{"Activate"};
    constexpr std::string_view cHomeToggleChannelButtonDeactivate{"Deactivate"};
    constexpr std::string_view cHomeTimerChannelLabel{"Use timer #"};
    constexpr std::string_view cHomeTimerChannelButtonStart{"Start"};
    constexpr std::string_view cHomeTimerChannelButtonStop{"Stop"};
    constexpr float cHomeStatusFraction{0.0};
    constexpr int cHomeBoxChannelMargin{10};
    constexpr int cHomeBoxChannelSpacing{5};
    constexpr std::string_view cHomeChannelModeOptions[]{"Toogle Active", "Timer Active"};
};

using namespace Electux::App::View;
using namespace Electux::App::Params::Channel;

AppHome::AppHome()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup application home window
    set_title(cHomeTitle.data());
    set_default_size(cHomeWidth, cHomeHeight);
    set_resizable(false);
    set_show_menubar(true);
    m_boxRoot.set_orientation(Gtk::Orientation::HORIZONTAL);
    set_child(m_boxRoot);

    for(unsigned int i = 0; i < cNumOfChannels; i++)
    {
        m_boxChannels.emplace_back(Gtk::Orientation::VERTICAL);
        auto& currentBox = m_boxChannels.back();
        m_enableChannels.emplace_back(std::format("{} {}", cHomeEnChannelLabel.data(), i));
        currentBox.append(m_enableChannels.back());
        m_selectControlChannels.emplace_back();
        for (const auto& option : cHomeChannelModeOptions)
        {
            m_selectControlChannels.back().append(option.data());
        }
        currentBox.append(m_selectControlChannels.back());
        m_labelToggleChannels.emplace_back(std::format("{} {}", cHomeToggleChannelLabel.data(), i));
        currentBox.append(m_labelToggleChannels.back());
        m_toggleChannels.emplace_back();
        m_toggleChannels.back().set_label(cHomeToggleChannelButtonActivate.data());
        currentBox.append(m_toggleChannels.back());
        m_labelTimerChannels.emplace_back(std::format("{} {}", cHomeTimerChannelLabel.data(), i));
        currentBox.append(m_labelTimerChannels.back());
        m_spinTimerChannels.emplace_back();
        currentBox.append(m_spinTimerChannels.back());
        m_toggleTimerChannels.emplace_back();
        m_toggleTimerChannels.back().set_label(cHomeTimerChannelButtonStart.data());
        currentBox.append(m_toggleTimerChannels.back());
        m_statusTimerChannels.emplace_back();
        m_statusTimerChannels.back().set_fraction(cHomeStatusFraction);
        currentBox.append(m_statusTimerChannels.back());
        currentBox.set_margin(cHomeBoxChannelMargin);
        currentBox.set_spacing(cHomeBoxChannelSpacing);
        m_boxRoot.append(currentBox);
        mapping(i);
    }
}

void AppHome::setControlSetup(const SettingsSetup& setup)
{
    m_controlSetup = setup;
}
