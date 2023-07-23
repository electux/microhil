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

#ifndef MICROHIL_VIEW_H
#define MICROHIL_VIEW_H

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <giomm/resource.h>
#include <gtkmm/checkbutton.h>
#include "microhil_view_if.h"

using BRefPtr = Glib::RefPtr<Gtk::Builder>;

class MicroHILView : public IMicroHILView, public Gtk::ApplicationWindow
{
public:
    MicroHILView(BaseObjectType* object, BRefPtr const& ui);
    ~MicroHILView();

    void onChannel0() final;
    void onChannel1() final;
    void onChannel2() final;
    void onChannel3() final;

    channel0Changed channel0IsChanged() final;
    channel1Changed channel1IsChanged() final;
    channel2Changed channel2IsChanged() final;
    channel3Changed channel3IsChanged() final;

private:
    BRefPtr ui;

    Gtk::CheckButton *m_checkButtonChannel0;
    Gtk::CheckButton *m_checkButtonChannel1;
    Gtk::CheckButton *m_checkButtonChannel2;
    Gtk::CheckButton *m_checkButtonChannel3;

    channel0Changed m_channel0;
    channel1Changed m_channel1;
    channel2Changed m_channel2;
    channel3Changed m_channel3;
};

#endif
