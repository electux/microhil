/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home.cc
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "microhil_view_home.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Number of channels
    constexpr int kNumberOfChannels {8};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Connect menu-item id
    constexpr const char kConnectId[]{"Connect"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Disconnect menu-item id
    constexpr const char kDisconnectId[]{"Disconnect"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Quit menu-item id
    constexpr const char kQuitId[]{"Quit"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Serial Settings menu-item id
    constexpr const char kSerialSettingsId[]{"HomeSerialPortSettings"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Log Settings menu-item id
    constexpr const char kLogSettingsId[]{"HomeLogSettings"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application About menu-item id
    constexpr const char kAboutId[]{"HomeAbout"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check buttons (UI ids)
    constexpr const char* kCheckButtonsId[]
    {
        "EnableChannel0",
        "EnableChannel1",
        "EnableChannel2",
        "EnableChannel3",
        "EnableChannel4",
        "EnableChannel5",
        "EnableChannel6",
        "EnableChannel7"
    };

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toggle buttons (UI ids)
    constexpr const char* kToggleButtonsId[]
    {
        "Channel0ToggleButton",
        "Channel1ToggleButton",
        "Channel2ToggleButton",
        "Channel3ToggleButton",
        "Channel4ToggleButton",
        "Channel5ToggleButton",
        "Channel6ToggleButton",
        "Channel7ToggleButton"
    };

    ////////////////////////////////////////////////////////////////////////
    /// @brief Comboboxes (UI ids)
    constexpr const char* kComboBoxTextsId[]
    {
        "Channel0Selector",
        "Channel1Selector",
        "Channel2Selector",
        "Channel3Selector",
        "Channel4Selector",
        "Channel5Selector",
        "Channel6Selector",
        "Channel7Selector"
    };

    ////////////////////////////////////////////////////////////////////////
    /// @brief Spin buttons (UI ids)
    constexpr const char* kTimerSpinButtonsId[]
    {
        "Channel0TimerSpin",
        "Channel1TimerSpin",
        "Channel2TimerSpin",
        "Channel3TimerSpin",
        "Channel4TimerSpin",
        "Channel5TimerSpin",
        "Channel6TimerSpin",
        "Channel7TimerSpin"
    };

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toogle buttons (UI ids)
    constexpr const char* kTimerToggleButtonsId[]
    {
        "Channel0TimerButton",
        "Channel1TimerButton",
        "Channel2TimerButton",
        "Channel3TimerButton",
        "Channel4TimerButton",
        "Channel5TimerButton",
        "Channel6TimerButton",
        "Channel7TimerButton"
    };

    ////////////////////////////////////////////////////////////////////////
    /// @brief Status bars (UI ids) 
    constexpr const char* kTimerProgressBarStatus0Id[]
    {
        "Channel0TimerStatus",
        "Channel1TimerStatus",
        "Channel2TimerStatus",
        "Channel3TimerStatus",
        "Channel4TimerStatus",
        "Channel5TimerStatus",
        "Channel6TimerStatus",
        "Channel7TimerStatus"
    };
}

MicroHILViewHome::MicroHILViewHome(
    BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
): Gtk::ApplicationWindow(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    // Bind Connect menu-item
    m_connect = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kConnectId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind Disconnect menu-item
    m_disconnect = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kDisconnectId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind Quit menu-item
    m_quit = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kQuitId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind Serial Settings menu-item
    m_serialSettings = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kSerialSettingsId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind Log Settings menu-item
    m_logSettings = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kLogSettingsId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind About menu-item
    m_about = Glib::RefPtr<Gtk::MenuItem>::cast_dynamic(
        m_ui->get_object(kAboutId)
    );

    ////////////////////////////////////////////////////////////////////////
    // Bind channels
    for (int i = 0; i < kNumberOfChannels; i++)
    {
        m_enableChannels.push_back(
            Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
                m_ui->get_object(kCheckButtonsId[i])
            )
        );
        m_selectControlChannels.push_back(
            Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
                m_ui->get_object(kComboBoxTextsId[i])
            )
        );
        m_toggleChannels.push_back(
            Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
                m_ui->get_object(kToggleButtonsId[i])
            )
        );
        m_spinTimerChannels.push_back(
            Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
                m_ui->get_object(kTimerSpinButtonsId[i])
            )
        );
        m_toggleTimerChannels.push_back(
            Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
                m_ui->get_object(kTimerToggleButtonsId[i])
            )
        );
        m_stautsTimerChannels.push_back(
            Glib::RefPtr<Gtk::ProgressBar>::cast_dynamic(
                m_ui->get_object(kTimerProgressBarStatus0Id[i])
            )
        );
    }

    ////////////////////////////////////////////////////////////////////////
    // Map channels (signals and slots)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    // Disabled all channels by default
    for (int i = 0; i < kNumberOfChannels; i++)
    {
        disableChannel(static_cast<Channel>(i));
    }
}
