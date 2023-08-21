/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_about.h
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

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/aboutdialog.h>
#include "microhil_view_about_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILViewAbout class declaration and definition 
class MicroHILViewAbout: public AbMicroHILViewAbout, public Gtk::AboutDialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewAbout constructor
    /// @param object base object type
    /// @param ui builder instance
    MicroHILViewAbout(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewAbout destructor
    ~MicroHILViewAbout() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    hideAbout hideAboutTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (self hide AboutDialog)
    void onHideAboutTriggered() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map Ok button (signal and slot)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Ok button for about view
    Glib::RefPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (self hide AboutDialog)
    hideAbout m_hideAbout{};
};
