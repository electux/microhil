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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <giomm/resource.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/progressbar.h>
#include "microhil_view_abstract.h"

class MicroHILView : public AbMicroHILView, public Gtk::ApplicationWindow
{
public:
    MicroHILView(BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui);
    ~MicroHILView() = default;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for enabling check buttons
    channel0Changed channel0IsChanged() final;
    channel1Changed channel1IsChanged() final;
    channel2Changed channel2IsChanged() final;
    channel3Changed channel3IsChanged() final;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for enabling check buttons
    void onChannel0() final;
    void onChannel1() final;
    void onChannel2() final;
    void onChannel3() final;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for selecting comboboxes
    select0Changed channel0IsSelected() final;
    select1Changed channel1IsSelected() final;
    select2Changed channel2IsSelected() final;
    select3Changed channel3IsSelected() final;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing comboboxes
    void onChannel0TypeSelected() final;
    void onChannel1TypeSelected() final;
    void onChannel2TypeSelected() final;
    void onChannel3TypeSelected() final;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for toggling buttons
    channel0Toggled channel0IsToggled() final;
    channel1Toggled channel1IsToggled() final;
    channel2Toggled channel2IsToggled() final;
    channel3Toggled channel3IsToggled() final;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for toggling buttons
    void onChannel0Toggled() final;
    void onChannel1Toggled() final;
    void onChannel2Toggled() final;
    void onChannel3Toggled() final;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from spin buttons (based on timer)
    channel0SpinTimerChanged channel0IsSpinTimerChanged() final;
    channel1SpinTimerChanged channel1IsSpinTimerChanged() final;
    channel2SpinTimerChanged channel2IsSpinTimerChanged() final;
    channel3SpinTimerChanged channel3IsSpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing spin buttons (based on timer)
    void onChannel0SpinTimerChanged() final;
    void onChannel1SpinTimerChanged() final;
    void onChannel2SpinTimerChanged() final;
    void onChannel3SpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from toggle buttons (based on timer)
    channel0TimerToggled channel0IsTimerChanged() final;
    channel1TimerToggled channel1IsTimerChanged() final;
    channel2TimerToggled channel2IsTimerChanged() final;
    channel3TimerToggled channel3IsTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing toggle buttons (turn on/turn off timer)
    void onChannel0TimerChanged() final;
    void onChannel1TimerChanged() final;
    void onChannel2TimerChanged() final;
    void onChannel3TimerChanged() final;

private:
    Glib::RefPtr<Gtk::Builder> m_ui;

    Glib::RefPtr<Gtk::CheckButton> m_enableChannel0;
    Glib::RefPtr<Gtk::CheckButton> m_enableChannel1;
    Glib::RefPtr<Gtk::CheckButton> m_enableChannel2;
    Glib::RefPtr<Gtk::CheckButton> m_enableChannel3;

    Glib::RefPtr<Gtk::ComboBoxText> m_selectControlChannel0;
    Glib::RefPtr<Gtk::ComboBoxText> m_selectControlChannel1;
    Glib::RefPtr<Gtk::ComboBoxText> m_selectControlChannel2;
    Glib::RefPtr<Gtk::ComboBoxText> m_selectControlChannel3;

    Glib::RefPtr<Gtk::ToggleButton> m_toggleChannel0;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleChannel1;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleChannel2;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleChannel3;

    Glib::RefPtr<Gtk::Adjustment> m_adjustment_digits;

    Glib::RefPtr<Gtk::SpinButton> m_spinTimerChannel0;
    Glib::RefPtr<Gtk::SpinButton> m_spinTimerChannel1;
    Glib::RefPtr<Gtk::SpinButton> m_spinTimerChannel2;
    Glib::RefPtr<Gtk::SpinButton> m_spinTimerChannel3;

    Glib::RefPtr<Gtk::ToggleButton> m_toggleTimerChannel0;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleTimerChannel1;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleTimerChannel2;
    Glib::RefPtr<Gtk::ToggleButton> m_toggleTimerChannel3;

    Glib::RefPtr<Gtk::ProgressBar> m_stautsTimerChannel0;
    Glib::RefPtr<Gtk::ProgressBar> m_stautsTimerChannel1;
    Glib::RefPtr<Gtk::ProgressBar> m_stautsTimerChannel2;
    Glib::RefPtr<Gtk::ProgressBar> m_stautsTimerChannel3;

    channel0Changed m_channel0Enabled;
    channel1Changed m_channel1Enabled;
    channel2Changed m_channel2Enabled;
    channel3Changed m_channel3Enabled;

    select0Changed m_channel0ControlType;
    select1Changed m_channel1ControlType;
    select2Changed m_channel2ControlType;
    select3Changed m_channel3ControlType;

    channel0Toggled m_channel0Toggled;
    channel1Toggled m_channel1Toggled;
    channel2Toggled m_channel2Toggled;
    channel3Toggled m_channel3Toggled;

    channel0SpinTimerChanged m_channel0SpinTimerChanged;
    channel1SpinTimerChanged m_channel1SpinTimerChanged;
    channel2SpinTimerChanged m_channel2SpinTimerChanged;
    channel3SpinTimerChanged m_channel3SpinTimerChanged;

    channel0TimerToggled m_channel0TimerToggled;
    channel1TimerToggled m_channel1TimerToggled;
    channel2TimerToggled m_channel2TimerToggled;
    channel3TimerToggled m_channel3TimerToggled;
};
