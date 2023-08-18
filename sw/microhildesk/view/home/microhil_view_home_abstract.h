/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_abstract.h
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

#include <sigc++/sigc++.h>

class AbMicroHILViewHome
{
public:
    ////////////////////////////////////////////////////////////////////////
    // Signal types for check buttons (enable/disable channel)
    using channel0Changed = sigc::signal<void(bool)>;
    using channel1Changed = sigc::signal<void(bool)>;
    using channel2Changed = sigc::signal<void(bool)>;
    using channel3Changed = sigc::signal<void(bool)>;
    using channel4Changed = sigc::signal<void(bool)>;
    using channel5Changed = sigc::signal<void(bool)>;
    using channel6Changed = sigc::signal<void(bool)>;
    using channel7Changed = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal types for selectable comboboxes (toogle/timer type control)
    using select0Changed = sigc::signal<void(int)>;
    using select1Changed = sigc::signal<void(int)>;
    using select2Changed = sigc::signal<void(int)>;
    using select3Changed = sigc::signal<void(int)>;
    using select4Changed = sigc::signal<void(int)>;
    using select5Changed = sigc::signal<void(int)>;
    using select6Changed = sigc::signal<void(int)>;
    using select7Changed = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal types for toogle buttons (turn on/turn off channel)
    using channel0Toggled = sigc::signal<void(bool)>;
    using channel1Toggled = sigc::signal<void(bool)>;
    using channel2Toggled = sigc::signal<void(bool)>;
    using channel3Toggled = sigc::signal<void(bool)>;
    using channel4Toggled = sigc::signal<void(bool)>;
    using channel5Toggled = sigc::signal<void(bool)>;
    using channel6Toggled = sigc::signal<void(bool)>;
    using channel7Toggled = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal types for spin buttons (based on timer setup)
    using channel0SpinTimerChanged = sigc::signal<void(int)>;
    using channel1SpinTimerChanged = sigc::signal<void(int)>;
    using channel2SpinTimerChanged = sigc::signal<void(int)>;
    using channel3SpinTimerChanged = sigc::signal<void(int)>;
    using channel4SpinTimerChanged = sigc::signal<void(int)>;
    using channel5SpinTimerChanged = sigc::signal<void(int)>;
    using channel6SpinTimerChanged = sigc::signal<void(int)>;
    using channel7SpinTimerChanged = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal types for toogle buttons (based on timer setup)
    using channel0TimerToggled = sigc::signal<void(bool)>;
    using channel1TimerToggled = sigc::signal<void(bool)>;
    using channel2TimerToggled = sigc::signal<void(bool)>;
    using channel3TimerToggled = sigc::signal<void(bool)>;
    using channel4TimerToggled = sigc::signal<void(bool)>;
    using channel5TimerToggled = sigc::signal<void(bool)>;
    using channel6TimerToggled = sigc::signal<void(bool)>;
    using channel7TimerToggled = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    // AbMicroHILViewHome destructor
    virtual ~AbMicroHILViewHome() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from check buttons (enable/disable channel)
    virtual channel0Changed channel0IsChanged() = 0;
    virtual channel1Changed channel1IsChanged() = 0;
    virtual channel2Changed channel2IsChanged() = 0;
    virtual channel3Changed channel3IsChanged() = 0;
    virtual channel4Changed channel4IsChanged() = 0;
    virtual channel5Changed channel5IsChanged() = 0;
    virtual channel6Changed channel6IsChanged() = 0;
    virtual channel7Changed channel7IsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing check buttons (enable/disable channel)
    virtual void onChannel0() = 0;
    virtual void onChannel1() = 0;
    virtual void onChannel2() = 0;
    virtual void onChannel3() = 0;
    virtual void onChannel4() = 0;
    virtual void onChannel5() = 0;
    virtual void onChannel6() = 0;
    virtual void onChannel7() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from selection comboboxes (control type)
    virtual select0Changed channel0IsSelected() = 0;
    virtual select1Changed channel1IsSelected() = 0;
    virtual select2Changed channel2IsSelected() = 0;
    virtual select3Changed channel3IsSelected() = 0;
    virtual select4Changed channel4IsSelected() = 0;
    virtual select5Changed channel5IsSelected() = 0;
    virtual select6Changed channel6IsSelected() = 0;
    virtual select7Changed channel7IsSelected() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing comboboxes (control type)
    virtual void onChannel0TypeSelected() = 0;
    virtual void onChannel1TypeSelected() = 0;
    virtual void onChannel2TypeSelected() = 0;
    virtual void onChannel3TypeSelected() = 0;
    virtual void onChannel4TypeSelected() = 0;
    virtual void onChannel5TypeSelected() = 0;
    virtual void onChannel6TypeSelected() = 0;
    virtual void onChannel7TypeSelected() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from toggling buttons (turn on/turn off channel)
    virtual channel0Toggled channel0IsToggled() = 0;
    virtual channel1Toggled channel1IsToggled() = 0;
    virtual channel2Toggled channel2IsToggled() = 0;
    virtual channel3Toggled channel3IsToggled() = 0;
    virtual channel4Toggled channel4IsToggled() = 0;
    virtual channel5Toggled channel5IsToggled() = 0;
    virtual channel6Toggled channel6IsToggled() = 0;
    virtual channel7Toggled channel7IsToggled() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing toggle buttons (turn on/turn off channel)
    virtual void onChannel0Toggled() = 0;
    virtual void onChannel1Toggled() = 0;
    virtual void onChannel2Toggled() = 0;
    virtual void onChannel3Toggled() = 0;
    virtual void onChannel4Toggled() = 0;
    virtual void onChannel5Toggled() = 0;
    virtual void onChannel6Toggled() = 0;
    virtual void onChannel7Toggled() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from spin buttons (based on timer)
    virtual channel0SpinTimerChanged channel0IsSpinTimerChanged() = 0;
    virtual channel1SpinTimerChanged channel1IsSpinTimerChanged() = 0;
    virtual channel2SpinTimerChanged channel2IsSpinTimerChanged() = 0;
    virtual channel3SpinTimerChanged channel3IsSpinTimerChanged() = 0;
    virtual channel4SpinTimerChanged channel4IsSpinTimerChanged() = 0;
    virtual channel5SpinTimerChanged channel5IsSpinTimerChanged() = 0;
    virtual channel6SpinTimerChanged channel6IsSpinTimerChanged() = 0;
    virtual channel7SpinTimerChanged channel7IsSpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing spin buttons (based on timer)
    virtual void onChannel0SpinTimerChanged() = 0;
    virtual void onChannel1SpinTimerChanged() = 0;
    virtual void onChannel2SpinTimerChanged() = 0;
    virtual void onChannel3SpinTimerChanged() = 0;
    virtual void onChannel4SpinTimerChanged() = 0;
    virtual void onChannel5SpinTimerChanged() = 0;
    virtual void onChannel6SpinTimerChanged() = 0;
    virtual void onChannel7SpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from toggle buttons (based on timer)
    virtual channel0TimerToggled channel0IsTimerChanged() = 0;
    virtual channel1TimerToggled channel1IsTimerChanged() = 0;
    virtual channel2TimerToggled channel2IsTimerChanged() = 0;
    virtual channel3TimerToggled channel3IsTimerChanged() = 0;
    virtual channel4TimerToggled channel4IsTimerChanged() = 0;
    virtual channel5TimerToggled channel5IsTimerChanged() = 0;
    virtual channel6TimerToggled channel6IsTimerChanged() = 0;
    virtual channel7TimerToggled channel7IsTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing toggle buttons (turn on/turn off timer)
    virtual void onChannel0TimerChanged() = 0;
    virtual void onChannel1TimerChanged() = 0;
    virtual void onChannel2TimerChanged() = 0;
    virtual void onChannel3TimerChanged() = 0;
    virtual void onChannel4TimerChanged() = 0;
    virtual void onChannel5TimerChanged() = 0;
    virtual void onChannel6TimerChanged() = 0;
    virtual void onChannel7TimerChanged() = 0;
};
