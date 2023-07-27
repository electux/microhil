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
}

MicroHILView::MicroHILView(
    BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
): Gtk::ApplicationWindow(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////////
    // Bind enable check buttons 
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
    // Bind control comboboxes 
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
    // Map signal for enable check buttons
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
    // Map signal for selecting comboboxes
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
