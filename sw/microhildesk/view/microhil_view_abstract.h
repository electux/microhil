/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_abstract.h
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

#include <sigc++/sigc++.h>

class AbMicroHILView
{
public:

    ////////////////////////////////////////////////////////////////////////////
    // Signal types for check buttons (enable/disable channel)
    using channel0Changed = sigc::signal<void(bool)>;
    using channel1Changed = sigc::signal<void(bool)>;
    using channel2Changed = sigc::signal<void(bool)>;
    using channel3Changed = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////////
    // Signal types for selectable comboboxes (toogle/timer type control)
    using select0Changed = sigc::signal<void(int)>;
    using select1Changed = sigc::signal<void(int)>;
    using select2Changed = sigc::signal<void(int)>;
    using select3Changed = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////////
    // Signal types for toogle buttons (turn on/turn off channel)
    using channel0Toggled = sigc::signal<void(bool)>;
    using channel1Toggled = sigc::signal<void(bool)>;
    using channel2Toggled = sigc::signal<void(bool)>;
    using channel3Toggled = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////////
    // Signal types for spin buttons (based on timer setup)
    using channel0SpinTimerChanged = sigc::signal<void(int)>;
    using channel1SpinTimerChanged = sigc::signal<void(int)>;
    using channel2SpinTimerChanged = sigc::signal<void(int)>;
    using channel3SpinTimerChanged = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////////
    // Signal types for toogle buttons (based on timer setup)
    using channel0TimerToggled = sigc::signal<void(bool)>;
    using channel1TimerToggled = sigc::signal<void(bool)>;
    using channel2TimerToggled = sigc::signal<void(bool)>;
    using channel3TimerToggled = sigc::signal<void(bool)>;

    virtual ~AbMicroHILView() = default;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from check buttons (enable/disable channel)
    virtual channel0Changed channel0IsChanged() = 0;
    virtual channel1Changed channel1IsChanged() = 0;
    virtual channel2Changed channel2IsChanged() = 0;
    virtual channel3Changed channel3IsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing check buttons (enable/disable channel)
    virtual void onChannel0() = 0;
    virtual void onChannel1() = 0;
    virtual void onChannel2() = 0;
    virtual void onChannel3() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from selection comboboxes (control type)
    virtual select0Changed channel0IsSelected() = 0;
    virtual select1Changed channel1IsSelected() = 0;
    virtual select2Changed channel2IsSelected() = 0;
    virtual select3Changed channel3IsSelected() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing comboboxes (control type)
    virtual void onChannel0TypeSelected() = 0;
    virtual void onChannel1TypeSelected() = 0;
    virtual void onChannel2TypeSelected() = 0;
    virtual void onChannel3TypeSelected() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from toggling buttons (turn on/turn off channel)
    virtual channel0Toggled channel0IsToggled() = 0;
    virtual channel1Toggled channel1IsToggled() = 0;
    virtual channel2Toggled channel2IsToggled() = 0;
    virtual channel3Toggled channel3IsToggled() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing toggle buttons (turn on/turn off channel)
    virtual void onChannel0Toggled() = 0;
    virtual void onChannel1Toggled() = 0;
    virtual void onChannel2Toggled() = 0;
    virtual void onChannel3Toggled() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from spin buttons (based on timer)
    virtual channel0SpinTimerChanged channel0IsSpinTimerChanged() = 0;
    virtual channel1SpinTimerChanged channel1IsSpinTimerChanged() = 0;
    virtual channel2SpinTimerChanged channel2IsSpinTimerChanged() = 0;
    virtual channel3SpinTimerChanged channel3IsSpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing spin buttons (based on timer)
    virtual void onChannel0SpinTimerChanged() = 0;
    virtual void onChannel1SpinTimerChanged() = 0;
    virtual void onChannel2SpinTimerChanged() = 0;
    virtual void onChannel3SpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Signals for emitting from toggle buttons (based on timer)
    virtual channel0TimerToggled channel0IsTimerChanged() = 0;
    virtual channel1TimerToggled channel1IsTimerChanged() = 0;
    virtual channel2TimerToggled channel2IsTimerChanged() = 0;
    virtual channel3TimerToggled channel3IsTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // Slots for processing toggle buttons (turn on/turn off timer)
    virtual void onChannel0TimerChanged() = 0;
    virtual void onChannel1TimerChanged() = 0;
    virtual void onChannel2TimerChanged() = 0;
    virtual void onChannel3TimerChanged() = 0;
};
