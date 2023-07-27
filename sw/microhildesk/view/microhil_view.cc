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
    constexpr char kCheckButton0Id[]{"EnableChannel0"};
    constexpr char kCheckButton1Id[]{"EnableChannel1"};
    constexpr char kCheckButton2Id[]{"EnableChannel2"};
    constexpr char kCheckButton3Id[]{"EnableChannel3"};

    constexpr char kComboBoxText0Id[]{"Channel0Selector"};
    constexpr char kComboBoxText1Id[]{"Channel1Selector"};
    constexpr char kComboBoxText2Id[]{"Channel2Selector"};
    constexpr char kComboBoxText3Id[]{"Channel3Selector"};

    constexpr char kToggleButton0Id[]{"Channel0ToggleButton"};
    constexpr char kToggleButton1Id[]{"Channel1ToggleButton"};
    constexpr char kToggleButton2Id[]{"Channel2ToggleButton"};
    constexpr char kToggleButton3Id[]{"Channel3ToggleButton"};

    constexpr char kTimerSpinButton0Id[]{"Channel0TimerSpin"};
    constexpr char kTimerSpinButton1Id[]{"Channel1TimerSpin"};
    constexpr char kTimerSpinButton2Id[]{"Channel2TimerSpin"};
    constexpr char kTimerSpinButton3Id[]{"Channel3TimerSpin"};

    constexpr char kTimerToggleButton0Id[]{"Channel0TimerButton"};
    constexpr char kTimerToggleButton1Id[]{"Channel1TimerButton"};
    constexpr char kTimerToggleButton2Id[]{"Channel2TimerButton"};
    constexpr char kTimerToggleButton3Id[]{"Channel3TimerButton"};

    constexpr char kTimerProgressBarStatus0Id[]{"Channel0TimerStatus"};
    constexpr char kTimerProgressBarStatus1Id[]{"Channel1TimerStatus"};
    constexpr char kTimerProgressBarStatus2Id[]{"Channel2TimerStatus"};
    constexpr char kTimerProgressBarStatus3Id[]{"Channel3TimerStatus"};
}

MicroHILView::MicroHILView(
    BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
): Gtk::ApplicationWindow(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////////
    // Bind enable/disable check buttons (enable/disable channel) 
    m_enableChannel0 = Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
        m_ui->get_object(kCheckButton0Id)
    );
    m_enableChannel1 = Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
        m_ui->get_object(kCheckButton1Id)
    );
    m_enableChannel2 = Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
        m_ui->get_object(kCheckButton2Id)
    );
    m_enableChannel3 = Glib::RefPtr<Gtk::CheckButton>::cast_dynamic(
        m_ui->get_object(kCheckButton3Id)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Bind control comboboxes (toogle/timer-toggle based control)
    m_selectControlChannel0 = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kComboBoxText0Id)
    );

    m_selectControlChannel1 = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kComboBoxText1Id)
    );

    m_selectControlChannel2 = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kComboBoxText2Id)
    );

    m_selectControlChannel3 = Glib::RefPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kComboBoxText3Id)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Map signals for enable/disable check buttons (enable/disable channel)
    m_enableChannel0->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0)
    );

    m_enableChannel1->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1)
    );

    m_enableChannel2->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2)
    );

    m_enableChannel3->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Map signals for selecting comboboxes (selecting type of control channel)
    m_selectControlChannel0->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TypeSelected)
    );

    m_selectControlChannel1->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TypeSelected)
    );

    m_selectControlChannel2->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TypeSelected)
    );

    m_selectControlChannel3->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3TypeSelected)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Bind toggle buttons (turn-on/turn-off channels)
    m_toggleChannel0 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kToggleButton0Id)
    );
    m_toggleChannel1 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kToggleButton1Id)
    );
    m_toggleChannel2 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kToggleButton2Id)
    );
    m_toggleChannel3 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kToggleButton3Id)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Map signals for toggle buttons (turn-on/turn-off channels)
    m_toggleChannel0->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0Toggled)
    );

    m_toggleChannel1->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1Toggled)
    );

    m_toggleChannel2->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2Toggled)
    );

    m_toggleChannel3->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3Toggled)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Bind spin buttons (setup timer)
    m_spinTimerChannel0 = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
        m_ui->get_object(kTimerSpinButton0Id)
    );
    m_spinTimerChannel1 = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
        m_ui->get_object(kTimerSpinButton1Id)
    );
    m_spinTimerChannel2 = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
        m_ui->get_object(kTimerSpinButton2Id)
    );
    m_spinTimerChannel3 = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
        m_ui->get_object(kTimerSpinButton3Id)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Map signals for spin buttons (setup timer)
    m_spinTimerChannel0->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0SpinTimerChanged)
    );

    m_spinTimerChannel1->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1SpinTimerChanged)
    );

    m_spinTimerChannel2->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2SpinTimerChanged)
    );

    m_spinTimerChannel3->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3SpinTimerChanged)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Bind toggle buttons (turn-on/turn-off timer)
    m_toggleTimerChannel0 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kTimerToggleButton0Id)
    );
    m_toggleTimerChannel1 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kTimerToggleButton1Id)
    );
    m_toggleTimerChannel2 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kTimerToggleButton2Id)
    );
    m_toggleTimerChannel3 = Glib::RefPtr<Gtk::ToggleButton>::cast_dynamic(
        m_ui->get_object(kTimerToggleButton3Id)
    );

    ////////////////////////////////////////////////////////////////////////////
    // Map signals for toggle buttons (based on timer)
    m_toggleTimerChannel0->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TimerChanged)
    );

    m_toggleTimerChannel1->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TimerChanged)
    );

    m_toggleTimerChannel2->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TimerChanged)
    );

    m_toggleTimerChannel3->signal_toggled().connect(
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
    bool status = m_enableChannel0->get_active();
    m_channel0Enabled.emit(status);
}

void MicroHILView::onChannel1()
{
    bool status = m_enableChannel1->get_active();
    m_channel1Enabled.emit(status);
}

void MicroHILView::onChannel2()
{
    bool status = m_enableChannel2->get_active();
    m_channel2Enabled.emit(status);
}

void MicroHILView::onChannel3()
{
    bool status = m_enableChannel3->get_active();
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
    int controlType = m_selectControlChannel0->get_active_row_number();
    m_channel0ControlType.emit(controlType);
}

void MicroHILView::onChannel1TypeSelected()
{
    int controlType = m_selectControlChannel1->get_active_row_number();
    m_channel1ControlType.emit(controlType);
}

void MicroHILView::onChannel2TypeSelected()
{
    int controlType = m_selectControlChannel2->get_active_row_number();
    m_channel2ControlType.emit(controlType);
}

void MicroHILView::onChannel3TypeSelected()
{
    int controlType = m_selectControlChannel3->get_active_row_number();
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
    bool status = m_toggleChannel0->get_active();
    m_channel0Toggled.emit(status);
}

void MicroHILView::onChannel1Toggled()
{
    bool status = m_toggleChannel1->get_active();
    m_channel1Toggled.emit(status);
}

void MicroHILView::onChannel2Toggled()
{
    bool status = m_toggleChannel2->get_active();
    m_channel2Toggled.emit(status);
}

void MicroHILView::onChannel3Toggled()
{
    bool status = m_toggleChannel3->get_active();
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
    int value = m_spinTimerChannel0->get_value_as_int();
    m_channel0SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel1SpinTimerChanged()
{
    int value = m_spinTimerChannel1->get_value_as_int();
    m_channel1SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel2SpinTimerChanged()
{
    int value = m_spinTimerChannel2->get_value_as_int();
    m_channel2SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel3SpinTimerChanged()
{
    int value = m_spinTimerChannel3->get_value_as_int();
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
    bool status = m_toggleTimerChannel0->get_active();
    m_channel0TimerToggled.emit(status);
}

void MicroHILView::onChannel1TimerChanged()
{
    bool status = m_toggleTimerChannel1->get_active();
    m_channel1TimerToggled.emit(status);
}

void MicroHILView::onChannel2TimerChanged()
{
    bool status = m_toggleTimerChannel2->get_active();
    m_channel2TimerToggled.emit(status);
}

void MicroHILView::onChannel3TimerChanged()
{
    bool status = m_toggleTimerChannel3->get_active();
    m_channel3TimerToggled.emit(status);
}
