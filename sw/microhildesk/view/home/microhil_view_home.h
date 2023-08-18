/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home.h
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
#include "microhil_view_home_abstract.h"

enum class channelControlType
{
    TOGGLE_BUTTON = 0,
    TIMER_BUTTON = 1
};

class MicroHILViewHome: public AbMicroHILViewHome, public Gtk::ApplicationWindow
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewHome constructor
    MicroHILViewHome(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewHome destructor
    ~MicroHILViewHome() = default;

    ////////////////////////////////////////////////////////////////////////
    // Enable/Disable channels by check buttons
    // Each check button enable or disable channel

    // Signal functions for check buttons
    channel0Changed channel0IsChanged() final;
    channel1Changed channel1IsChanged() final;
    channel2Changed channel2IsChanged() final;
    channel3Changed channel3IsChanged() final;
    channel4Changed channel4IsChanged() final;
    channel5Changed channel5IsChanged() final;
    channel6Changed channel6IsChanged() final;
    channel7Changed channel7IsChanged() final;

    // Slot functions for check buttons
    void onChannel0() final;
    void onChannel1() final;
    void onChannel2() final;
    void onChannel3() final;
    void onChannel4() final;
    void onChannel5() final;
    void onChannel6() final;
    void onChannel7() final;

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
    select4Changed channel4IsSelected() final;
    select5Changed channel5IsSelected() final;
    select6Changed channel6IsSelected() final;
    select7Changed channel7IsSelected() final;

    // Slot functions for processing comboboxes
    void onChannel0TypeSelected() final;
    void onChannel1TypeSelected() final;
    void onChannel2TypeSelected() final;
    void onChannel3TypeSelected() final;
    void onChannel4TypeSelected() final;
    void onChannel5TypeSelected() final;
    void onChannel6TypeSelected() final;
    void onChannel7TypeSelected() final;

    ////////////////////////////////////////////////////////////////////////
    // Control channel state ON/OFF
    // Functions for signals and slots (toggle buttons)

    // Signal functions for toggling buttons
    channel0Toggled channel0IsToggled() final;
    channel1Toggled channel1IsToggled() final;
    channel2Toggled channel2IsToggled() final;
    channel3Toggled channel3IsToggled() final;
    channel4Toggled channel4IsToggled() final;
    channel5Toggled channel5IsToggled() final;
    channel6Toggled channel6IsToggled() final;
    channel7Toggled channel7IsToggled() final;

    // Slot functions for toggling buttons
    void onChannel0Toggled() final;
    void onChannel1Toggled() final;
    void onChannel2Toggled() final;
    void onChannel3Toggled() final;
    void onChannel4Toggled() final;
    void onChannel5Toggled() final;
    void onChannel6Toggled() final;
    void onChannel7Toggled() final;

    ////////////////////////////////////////////////////////////////////////
    // Setup timers with spin buttons
    // The spin buttons are increasing and decreasing in seconds

    // Signal functions for emitting from spin buttons (based on timer)
    channel0SpinTimerChanged channel0IsSpinTimerChanged() final;
    channel1SpinTimerChanged channel1IsSpinTimerChanged() final;
    channel2SpinTimerChanged channel2IsSpinTimerChanged() final;
    channel3SpinTimerChanged channel3IsSpinTimerChanged() final;
    channel4SpinTimerChanged channel4IsSpinTimerChanged() final;
    channel5SpinTimerChanged channel5IsSpinTimerChanged() final;
    channel6SpinTimerChanged channel6IsSpinTimerChanged() final;
    channel7SpinTimerChanged channel7IsSpinTimerChanged() final;

    // Slot functions for processing spin buttons (based on timer)
    void onChannel0SpinTimerChanged() final;
    void onChannel1SpinTimerChanged() final;
    void onChannel2SpinTimerChanged() final;
    void onChannel3SpinTimerChanged() final;
    void onChannel4SpinTimerChanged() final;
    void onChannel5SpinTimerChanged() final;
    void onChannel6SpinTimerChanged() final;
    void onChannel7SpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Control start and stop operations for the timer per channel
    // Each channel has its own controllable timer

    // Signal functions for emitting from toggle buttons (based on timer)
    channel0TimerToggled channel0IsTimerChanged() final;
    channel1TimerToggled channel1IsTimerChanged() final;
    channel2TimerToggled channel2IsTimerChanged() final;
    channel3TimerToggled channel3IsTimerChanged() final;
    channel4TimerToggled channel4IsTimerChanged() final;
    channel5TimerToggled channel5IsTimerChanged() final;
    channel6TimerToggled channel6IsTimerChanged() final;
    channel7TimerToggled channel7IsTimerChanged() final;

    // Slot functions for processing toggle buttons (turn on/turn off timer)
    void onChannel0TimerChanged() final;
    void onChannel1TimerChanged() final;
    void onChannel2TimerChanged() final;
    void onChannel3TimerChanged() final;
    void onChannel4TimerChanged() final;
    void onChannel5TimerChanged() final;
    void onChannel6TimerChanged() final;
    void onChannel7TimerChanged() final;

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
    void enableChannel4();
    void disableChannel4();
    void enableChannel5();
    void disableChannel5();
    void enableChannel6();
    void disableChannel6();
    void enableChannel7();
    void disableChannel7();

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
    void toggleModeChannel4();
    void timerModeChannel4();
    void toggleModeChannel5();
    void timerModeChannel5();
    void toggleModeChannel6();
    void timerModeChannel6();
    void toggleModeChannel7();
    void timerModeChannel7();

    ////////////////////////////////////////////////////////////////////////
    // UI builder
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    // Widgets for home view
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
    channel4Changed m_channel4Enabled;
    channel5Changed m_channel5Enabled;
    channel6Changed m_channel6Enabled;
    channel7Changed m_channel7Enabled;

    ////////////////////////////////////////////////////////////////////////
    // Signals for selectable comboboxes (toogle/timer type control)
    select0Changed m_channel0ControlType;
    select1Changed m_channel1ControlType;
    select2Changed m_channel2ControlType;
    select3Changed m_channel3ControlType;
    select4Changed m_channel4ControlType;
    select5Changed m_channel5ControlType;
    select6Changed m_channel6ControlType;
    select7Changed m_channel7ControlType;

    ////////////////////////////////////////////////////////////////////////
    // Signals for toogle buttons (turn on/turn off channel)
    channel0Toggled m_channel0Toggled;
    channel1Toggled m_channel1Toggled;
    channel2Toggled m_channel2Toggled;
    channel3Toggled m_channel3Toggled;
    channel4Toggled m_channel4Toggled;
    channel5Toggled m_channel5Toggled;
    channel6Toggled m_channel6Toggled;
    channel7Toggled m_channel7Toggled;

    ////////////////////////////////////////////////////////////////////////
    // Signals for spin buttons (based on timer setup)
    channel0SpinTimerChanged m_channel0SpinTimerChanged;
    channel1SpinTimerChanged m_channel1SpinTimerChanged;
    channel2SpinTimerChanged m_channel2SpinTimerChanged;
    channel3SpinTimerChanged m_channel3SpinTimerChanged;
    channel4SpinTimerChanged m_channel4SpinTimerChanged;
    channel5SpinTimerChanged m_channel5SpinTimerChanged;
    channel6SpinTimerChanged m_channel6SpinTimerChanged;
    channel7SpinTimerChanged m_channel7SpinTimerChanged;

    ////////////////////////////////////////////////////////////////////////
    // Signals for toogle buttons (based on timer setup)
    channel0TimerToggled m_channel0TimerToggled;
    channel1TimerToggled m_channel1TimerToggled;
    channel2TimerToggled m_channel2TimerToggled;
    channel3TimerToggled m_channel3TimerToggled;
    channel4TimerToggled m_channel4TimerToggled;
    channel5TimerToggled m_channel5TimerToggled;
    channel6TimerToggled m_channel6TimerToggled;
    channel7TimerToggled m_channel7TimerToggled;
};
