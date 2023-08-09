/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view.cc
 * Copyright (C) 2021 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "microhil_view.h"

namespace
{
    constexpr int kNumberOfChannels {4};

    constexpr const char* kCheckButtonsId[]
    {
        "EnableChannel0",
        "EnableChannel1",
        "EnableChannel2",
        "EnableChannel3"
    };

    constexpr const char* kToggleButtonsId[]
    {
        "Channel0ToggleButton",
        "Channel1ToggleButton",
        "Channel2ToggleButton",
        "Channel3ToggleButton"
    };

    constexpr const char* kComboBoxTextsId[]
    {
        "Channel0Selector",
        "Channel1Selector",
        "Channel2Selector",
        "Channel3Selector"
    };

    constexpr const char* kTimerSpinButtonsId[]
    {
        "Channel0TimerSpin",
        "Channel1TimerSpin",
        "Channel2TimerSpin",
        "Channel3TimerSpin"
    };

    constexpr const char* kTimerToggleButtonsId[]
    {
        "Channel0TimerButton",
        "Channel1TimerButton",
        "Channel2TimerButton",
        "Channel3TimerButton"
    };

    constexpr const char* kTimerProgressBarStatus0Id[]
    {
        "Channel0TimerStatus",
        "Channel1TimerStatus",
        "Channel2TimerStatus",
        "Channel3TimerStatus"
    };
}

MicroHILView::MicroHILView(
    BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
): Gtk::ApplicationWindow(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    // Bind channel widgets
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
    // Map channel signals and slots
    mapping();

    ////////////////////////////////////////////////////////////////////////
    // Disabled all channels by default
    disableChannel0();
    disableChannel1();
    disableChannel2();
    disableChannel3();
}

void MicroHILView::disableChannel0()
{
    m_selectControlChannels[0]->set_sensitive(false);
    m_toggleChannels[0]->set_sensitive(false);
    m_spinTimerChannels[0]->set_sensitive(false);
    m_toggleTimerChannels[0]->set_sensitive(false);
    m_stautsTimerChannels[0]->set_sensitive(false);
}

void MicroHILView::enableChannel0()
{
    m_selectControlChannels[0]->set_sensitive(true);
    m_toggleChannels[0]->set_sensitive(true);
    m_spinTimerChannels[0]->set_sensitive(true);
    m_toggleTimerChannels[0]->set_sensitive(true);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILView::disableChannel1()
{
    m_selectControlChannels[1]->set_sensitive(false);
    m_toggleChannels[1]->set_sensitive(false);
    m_spinTimerChannels[1]->set_sensitive(false);
    m_toggleTimerChannels[1]->set_sensitive(false);
    m_stautsTimerChannels[1]->set_sensitive(false);
}

void MicroHILView::enableChannel1()
{
    m_selectControlChannels[1]->set_sensitive(true);
    m_toggleChannels[1]->set_sensitive(true);
    m_spinTimerChannels[1]->set_sensitive(true);
    m_toggleTimerChannels[1]->set_sensitive(true);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILView::disableChannel2()
{
    m_selectControlChannels[2]->set_sensitive(false);
    m_toggleChannels[2]->set_sensitive(false);
    m_spinTimerChannels[2]->set_sensitive(false);
    m_toggleTimerChannels[2]->set_sensitive(false);
    m_stautsTimerChannels[2]->set_sensitive(false);
}

void MicroHILView::enableChannel2()
{
    m_selectControlChannels[2]->set_sensitive(true);
    m_toggleChannels[2]->set_sensitive(true);
    m_spinTimerChannels[2]->set_sensitive(true);
    m_toggleTimerChannels[2]->set_sensitive(true);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILView::disableChannel3()
{
    m_selectControlChannels[3]->set_sensitive(false);
    m_toggleChannels[3]->set_sensitive(false);
    m_spinTimerChannels[3]->set_sensitive(false);
    m_toggleTimerChannels[3]->set_sensitive(false);
    m_stautsTimerChannels[3]->set_sensitive(false);
}

void MicroHILView::enableChannel3()
{
    m_selectControlChannels[3]->set_sensitive(true);
    m_toggleChannels[3]->set_sensitive(true);
    m_spinTimerChannels[3]->set_sensitive(true);
    m_toggleTimerChannels[3]->set_sensitive(true);
    m_stautsTimerChannels[3]->set_sensitive(true);
}

void MicroHILView::toggleModeChannel0()
{
    m_toggleChannels[0]->set_sensitive(true);
    m_spinTimerChannels[0]->set_sensitive(false);
    m_toggleTimerChannels[0]->set_sensitive(false);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILView::timerModeChannel0()
{
    m_toggleChannels[0]->set_sensitive(false);
    m_spinTimerChannels[0]->set_sensitive(true);
    m_toggleTimerChannels[0]->set_sensitive(true);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILView::toggleModeChannel1()
{
    m_toggleChannels[1]->set_sensitive(true);
    m_spinTimerChannels[1]->set_sensitive(false);
    m_toggleTimerChannels[1]->set_sensitive(false);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILView::timerModeChannel1()
{
    m_toggleChannels[1]->set_sensitive(false);
    m_spinTimerChannels[1]->set_sensitive(true);
    m_toggleTimerChannels[1]->set_sensitive(true);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILView::toggleModeChannel2()
{
    m_toggleChannels[2]->set_sensitive(true);
    m_spinTimerChannels[2]->set_sensitive(false);
    m_toggleTimerChannels[2]->set_sensitive(false);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILView::timerModeChannel2()
{
    m_toggleChannels[2]->set_sensitive(false);
    m_spinTimerChannels[2]->set_sensitive(true);
    m_toggleTimerChannels[2]->set_sensitive(true);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILView::toggleModeChannel3()
{
    m_toggleChannels[3]->set_sensitive(true);
    m_spinTimerChannels[3]->set_sensitive(false);
    m_toggleTimerChannels[3]->set_sensitive(false);
    m_stautsTimerChannels[3]->set_sensitive(true);
}

void MicroHILView::timerModeChannel3()
{
    m_toggleChannels[3]->set_sensitive(false);
    m_spinTimerChannels[3]->set_sensitive(true);
    m_toggleTimerChannels[3]->set_sensitive(true);
    m_stautsTimerChannels[3]->set_sensitive(true);
}
