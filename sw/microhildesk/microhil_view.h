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

    channel0Changed m_channel0Enabled;
    channel1Changed m_channel1Enabled;
    channel2Changed m_channel2Enabled;
    channel3Changed m_channel3Enabled;

    select0Changed m_channel0ControlType;
    select1Changed m_channel1ControlType;
    select2Changed m_channel2ControlType;
    select3Changed m_channel3ControlType;
};
