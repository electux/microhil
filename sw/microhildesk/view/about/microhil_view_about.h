/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_about.h
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

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/aboutdialog.h>
#include "microhil_view_about_abstract.h"

class MicroHILViewAbout : public AbMicroHILViewAbout, public Gtk::AboutDialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewAbout constructor
    MicroHILViewAbout(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewAbout destructor
    ~MicroHILViewAbout() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from about Ok button
    visibleAbout visibleAboutChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing Ok button for about dialog
    void onVisibleAboutChange() final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Map Ok button signal and slot
    void mapping();

    Glib::RefPtr<Gtk::Builder> m_ui;
    Glib::RefPtr<Gtk::Button> m_ok;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Ok button (hide about dialog)
    visibleAbout m_visibleAbout;
};
