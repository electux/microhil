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
#include <iostream>
#include "microhil_view.h"

namespace
{
    constexpr char kCheckButton0Id[]{"EnableChannel0"};
    constexpr char kCheckButton1Id[]{"EnableChannel1"};
    constexpr char kCheckButton2Id[]{"EnableChannel2"};
    constexpr char kCheckButton3Id[]{"EnableChannel3"};
}

MicroHILView::MicroHILView(BaseObjectType* object, BRefPtr const& ui):
Gtk::ApplicationWindow(object), ui{ui}
{
    ui->get_widget(kCheckButton0Id, m_checkButtonChannel0);
    ui->get_widget(kCheckButton1Id, m_checkButtonChannel1);
    ui->get_widget(kCheckButton2Id, m_checkButtonChannel2);
    ui->get_widget(kCheckButton3Id, m_checkButtonChannel3);

    m_checkButtonChannel0->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0)
    );

    m_checkButtonChannel1->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1)
    );

    m_checkButtonChannel2->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2)
    );

    m_checkButtonChannel3->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3)
    );
}

void MicroHILView::onChannel0()
{
    bool status = m_checkButtonChannel0->get_active();
    m_channel0.emit(status);
}

void MicroHILView::onChannel1()
{
    bool status = m_checkButtonChannel1->get_active();
    m_channel1.emit(status);
}

void MicroHILView::onChannel2()
{
    bool status = m_checkButtonChannel2->get_active();
    m_channel2.emit(status);
}

void MicroHILView::onChannel3()
{
    bool status = m_checkButtonChannel3->get_active();
    m_channel3.emit(status);
}

MicroHILView::channel0Changed MicroHILView::channel0IsChanged()
{
    return m_channel0;
}

MicroHILView::channel1Changed MicroHILView::channel1IsChanged()
{
    return m_channel1;
}

MicroHILView::channel2Changed MicroHILView::channel2IsChanged()
{
    return m_channel2;
}

MicroHILView::channel3Changed MicroHILView::channel3IsChanged()
{
    return m_channel3;
}

MicroHILView::~MicroHILView()
{
    if(m_checkButtonChannel0) delete m_checkButtonChannel0;
    if(m_checkButtonChannel1) delete m_checkButtonChannel1;
    if(m_checkButtonChannel2) delete m_checkButtonChannel2;
    if(m_checkButtonChannel3) delete m_checkButtonChannel3;
}
