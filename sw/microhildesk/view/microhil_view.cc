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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_view.h"

namespace
{
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
    ////////////////////////////////////////////////////////////////////////////
    // Bind channel widgets
    for (int i = 0; i < 4; i++)
    {
        m_enableChannels.push_back(
            Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
                m_ui->get_object(kCheckButtonsId[i])
            )
        );
        m_toggleChannels.push_back(
            Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
                m_ui->get_object(kToggleButtonsId[i])
            )
        );
        m_selectControlChannels.push_back(
            Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
                m_ui->get_object(kComboBoxTextsId[i])
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
    }

    ////////////////////////////////////////////////////////////////////////////
    // Map channel signals and slots
    m_enableChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0)
    );

    m_enableChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1)
    );

    m_enableChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2)
    );

    m_enableChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3)
    );

    m_selectControlChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TypeSelected)
    );

    m_selectControlChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TypeSelected)
    );

    m_selectControlChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TypeSelected)
    );

    m_selectControlChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3TypeSelected)
    );

    m_toggleChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0Toggled)
    );

    m_toggleChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1Toggled)
    );

    m_toggleChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2Toggled)
    );

    m_toggleChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3Toggled)
    );

    m_spinTimerChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0SpinTimerChanged)
    );

    m_spinTimerChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1SpinTimerChanged)
    );

    m_spinTimerChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2SpinTimerChanged)
    );

    m_spinTimerChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3SpinTimerChanged)
    );

    m_toggleTimerChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TimerChanged)
    );

    m_toggleTimerChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TimerChanged)
    );

    m_toggleTimerChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TimerChanged)
    );

    m_toggleTimerChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3TimerChanged)
    );
}

MicroHILView::channel0Changed MicroHILView::channel0IsChanged()
{
    return m_channel0Enabled;
}

MicroHILView::channel1Changed MicroHILView::channel1IsChanged()
{
    return m_channel1Enabled;
}

MicroHILView::channel2Changed MicroHILView::channel2IsChanged()
{
    return m_channel2Enabled;
}

MicroHILView::channel3Changed MicroHILView::channel3IsChanged()
{
    return m_channel3Enabled;
}

void MicroHILView::onChannel0()
{
    bool status = m_enableChannels[0]->get_active();
    m_channel0Enabled.emit(status);
}

void MicroHILView::onChannel1()
{
    bool status = m_enableChannels[1]->get_active();
    m_channel1Enabled.emit(status);
}

void MicroHILView::onChannel2()
{
    bool status = m_enableChannels[2]->get_active();
    m_channel2Enabled.emit(status);
}

void MicroHILView::onChannel3()
{
    bool status = m_enableChannels[3]->get_active();
    m_channel3Enabled.emit(status);
}

MicroHILView::select0Changed MicroHILView::channel0IsSelected()
{
    return m_channel0ControlType;
}

MicroHILView::select1Changed MicroHILView::channel1IsSelected()
{
    return m_channel1ControlType;
}

MicroHILView::select2Changed MicroHILView::channel2IsSelected()
{
    return m_channel2ControlType;
}

MicroHILView::select3Changed MicroHILView::channel3IsSelected()
{
    return m_channel3ControlType;
}

void MicroHILView::onChannel0TypeSelected()
{
    int controlType = m_selectControlChannels[0]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel0ControlType.emit(controlType);
}

void MicroHILView::onChannel1TypeSelected()
{
    int controlType = m_selectControlChannels[1]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel1ControlType.emit(controlType);
}

void MicroHILView::onChannel2TypeSelected()
{
    int controlType = m_selectControlChannels[2]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel2ControlType.emit(controlType);
}

void MicroHILView::onChannel3TypeSelected()
{
    int controlType = m_selectControlChannels[3]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel3ControlType.emit(controlType);
}

MicroHILView::channel0Toggled MicroHILView::channel0IsToggled()
{
    return m_channel0Toggled;
}

MicroHILView::channel1Toggled MicroHILView::channel1IsToggled()
{
    return m_channel1Toggled;
}

MicroHILView::channel2Toggled MicroHILView::channel2IsToggled()
{
    return m_channel2Toggled;
}

MicroHILView::channel3Toggled MicroHILView::channel3IsToggled()
{
    return m_channel3Toggled;
}

void MicroHILView::onChannel0Toggled()
{
    bool status = m_toggleChannels[0]->get_active();
    m_channel0Toggled.emit(status);
}

void MicroHILView::onChannel1Toggled()
{
    bool status = m_toggleChannels[1]->get_active();
    m_channel1Toggled.emit(status);
}

void MicroHILView::onChannel2Toggled()
{
    bool status = m_toggleChannels[2]->get_active();
    m_channel2Toggled.emit(status);
}

void MicroHILView::onChannel3Toggled()
{
    bool status = m_toggleChannels[3]->get_active();
    m_channel3Toggled.emit(status);
}

MicroHILView::channel0SpinTimerChanged
MicroHILView::channel0IsSpinTimerChanged()
{
    return m_channel0SpinTimerChanged;
}

MicroHILView::channel1SpinTimerChanged
MicroHILView::channel1IsSpinTimerChanged()
{
    return m_channel1SpinTimerChanged;
}

MicroHILView::channel2SpinTimerChanged
MicroHILView::channel2IsSpinTimerChanged()
{
    return m_channel2SpinTimerChanged;
}

MicroHILView::channel3SpinTimerChanged
MicroHILView::channel3IsSpinTimerChanged()
{
    return m_channel3SpinTimerChanged;
}

void MicroHILView::onChannel0SpinTimerChanged()
{
    int value = m_spinTimerChannels[0]->get_value_as_int();
    m_channel0SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel1SpinTimerChanged()
{
    int value = m_spinTimerChannels[1]->get_value_as_int();
    m_channel1SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel2SpinTimerChanged()
{
    int value = m_spinTimerChannels[2]->get_value_as_int();
    m_channel2SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel3SpinTimerChanged()
{
    int value = m_spinTimerChannels[3]->get_value_as_int();
    m_channel3SpinTimerChanged.emit(value);
}

MicroHILView::channel0TimerToggled MicroHILView::channel0IsTimerChanged()
{
    return m_channel0TimerToggled;
}

MicroHILView::channel1TimerToggled MicroHILView::channel1IsTimerChanged()
{
    return m_channel1TimerToggled;
}

MicroHILView::channel2TimerToggled MicroHILView::channel2IsTimerChanged()
{
    return m_channel2TimerToggled;
}

MicroHILView::channel3TimerToggled MicroHILView::channel3IsTimerChanged()
{
    return m_channel3TimerToggled;
}

void MicroHILView::onChannel0TimerChanged()
{
    bool status = m_toggleTimerChannels[0]->get_active();
    m_channel0TimerToggled.emit(status);
}

void MicroHILView::onChannel1TimerChanged()
{
    bool status = m_toggleTimerChannels[1]->get_active();
    m_channel1TimerToggled.emit(status);
}

void MicroHILView::onChannel2TimerChanged()
{
    bool status = m_toggleTimerChannels[2]->get_active();
    m_channel2TimerToggled.emit(status);
}

void MicroHILView::onChannel3TimerChanged()
{
    bool status = m_toggleTimerChannels[3]->get_active();
    m_channel3TimerToggled.emit(status);
}
