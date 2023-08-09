/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view.h
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
#pragma once

#include <vector>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <giomm/resource.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/progressbar.h>
#include "microhil_view_abstract.h"

enum class channelControlType
{
    TOGGLE_BUTTON = 0,
    TIMER_BUTTON = 1
};

class MicroHILView : public AbMicroHILView, public Gtk::ApplicationWindow
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILView constructor
    MicroHILView(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILView destructor
    ~MicroHILView() = default;

    ////////////////////////////////////////////////////////////////////////
    // Enable/Disable channels by check buttons
    // Each check button enable or disable channel

    // Signal functions for check buttons
    channel0Changed channel0IsChanged() final;
    channel1Changed channel1IsChanged() final;
    channel2Changed channel2IsChanged() final;
    channel3Changed channel3IsChanged() final;

    // Slot functions for check buttons
    void onChannel0() final;
    void onChannel1() final;
    void onChannel2() final;
    void onChannel3() final;

    ////////////////////////////////////////////////////////////////////////
    // Select control type by comboboxes
    // Currently two types of control:
    //  * using only toggle-button for ON/OFF, or
    //  * timers in combination with toggle buttons

    // Signal functions for selecting comboboxes
    select0Changed channel0IsSelected() final;
    select1Changed channel1IsSelected() final;
    select2Changed channel2IsSelected() final;
    select3Changed channel3IsSelected() final;

    // Slot functions for processing comboboxes
    void onChannel0TypeSelected() final;
    void onChannel1TypeSelected() final;
    void onChannel2TypeSelected() final;
    void onChannel3TypeSelected() final;

    ////////////////////////////////////////////////////////////////////////
    // Control channel state ON/OFF
    // Functions for signals and slots (toggle buttons)

    // Signal functions for toggling buttons
    channel0Toggled channel0IsToggled() final;
    channel1Toggled channel1IsToggled() final;
    channel2Toggled channel2IsToggled() final;
    channel3Toggled channel3IsToggled() final;

    // Slot functions for toggling buttons
    void onChannel0Toggled() final;
    void onChannel1Toggled() final;
    void onChannel2Toggled() final;
    void onChannel3Toggled() final;

    ////////////////////////////////////////////////////////////////////////
    // Setup timers with spin buttons
    // The spin buttons are increasing and decreasing in seconds

    // Signal functions for emitting from spin buttons (based on timer)
    channel0SpinTimerChanged channel0IsSpinTimerChanged() final;
    channel1SpinTimerChanged channel1IsSpinTimerChanged() final;
    channel2SpinTimerChanged channel2IsSpinTimerChanged() final;
    channel3SpinTimerChanged channel3IsSpinTimerChanged() final;

    // Slot functions for processing spin buttons (based on timer)
    void onChannel0SpinTimerChanged() final;
    void onChannel1SpinTimerChanged() final;
    void onChannel2SpinTimerChanged() final;
    void onChannel3SpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Control start and stop operations for the timer per channel
    // Each channel has its own controllable timer

    // Signal functions for emitting from toggle buttons (based on timer)
    channel0TimerToggled channel0IsTimerChanged() final;
    channel1TimerToggled channel1IsTimerChanged() final;
    channel2TimerToggled channel2IsTimerChanged() final;
    channel3TimerToggled channel3IsTimerChanged() final;

    // Slot functions for processing toggle buttons (turn on/turn off timer)
    void onChannel0TimerChanged() final;
    void onChannel1TimerChanged() final;
    void onChannel2TimerChanged() final;
    void onChannel3TimerChanged() final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Map channel signals and slots
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    // Enable/Disable complete channel
    void enableChannel0();
    void disableChannel0();
    void enableChannel1();
    void disableChannel1();
    void enableChannel2();
    void disableChannel2();
    void enableChannel3();
    void disableChannel3();

    ////////////////////////////////////////////////////////////////////////
    // Setup channel mode
    void toggleModeChannel0();
    void timerModeChannel0();
    void toggleModeChannel1();
    void timerModeChannel1();
    void toggleModeChannel2();
    void timerModeChannel2();
    void toggleModeChannel3();
    void timerModeChannel3();

    Glib::RefPtr<Gtk::Builder> m_ui;
    std::vector<Glib::RefPtr<Gtk::CheckButton>> m_enableChannels;
    std::vector<Glib::RefPtr<Gtk::ComboBoxText>> m_selectControlChannels;
    std::vector<Glib::RefPtr<Gtk::ToggleButton>> m_toggleChannels;
    std::vector<Glib::RefPtr<Gtk::SpinButton>> m_spinTimerChannels;
    std::vector<Glib::RefPtr<Gtk::ToggleButton>> m_toggleTimerChannels;
    std::vector<Glib::RefPtr<Gtk::ProgressBar>> m_stautsTimerChannels; 
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_digits;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from check buttons (enable/disable channel)
    channel0Changed m_channel0Enabled;
    channel1Changed m_channel1Enabled;
    channel2Changed m_channel2Enabled;
    channel3Changed m_channel3Enabled;

    ////////////////////////////////////////////////////////////////////////
    // Signals for selectable comboboxes (toogle/timer type control)
    select0Changed m_channel0ControlType;
    select1Changed m_channel1ControlType;
    select2Changed m_channel2ControlType;
    select3Changed m_channel3ControlType;

    ////////////////////////////////////////////////////////////////////////
    // Signals for toogle buttons (turn on/turn off channel)
    channel0Toggled m_channel0Toggled;
    channel1Toggled m_channel1Toggled;
    channel2Toggled m_channel2Toggled;
    channel3Toggled m_channel3Toggled;

    ////////////////////////////////////////////////////////////////////////
    // Signals for spin buttons (based on timer setup)
    channel0SpinTimerChanged m_channel0SpinTimerChanged;
    channel1SpinTimerChanged m_channel1SpinTimerChanged;
    channel2SpinTimerChanged m_channel2SpinTimerChanged;
    channel3SpinTimerChanged m_channel3SpinTimerChanged;

    ////////////////////////////////////////////////////////////////////////
    // Signals for toogle buttons (based on timer setup)
    channel0TimerToggled m_channel0TimerToggled;
    channel1TimerToggled m_channel1TimerToggled;
    channel2TimerToggled m_channel2TimerToggled;
    channel3TimerToggled m_channel3TimerToggled;
};
