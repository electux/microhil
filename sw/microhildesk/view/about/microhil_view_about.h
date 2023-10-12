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

#include "../../utils/microhil_types.h"
#include "microhil_view_about_abstract.h"
#include <gtkmm/aboutdialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>

////////////////////////////////////////////////////////////////////////////
/// @brief MHViewAbout class declaration and definition
class MHViewAbout : public AbMHViewAbout, public Gtk::AboutDialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewAbout constructor
    /// @param object represents base object type
    /// @param ui represents builder instance
    MHViewAbout(BaseObjectType *object, RPtr<Gtk::Builder> const &ui);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewAbout destructor
    inline ~MHViewAbout() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    SigHideAbout hideAboutTriggered() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (self hide AboutDialog)
    void onHideAboutTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps Ok button (signal and slot)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    RPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Ok button for about view
    RPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (self hide AboutDialog)
    SigHideAbout m_hideAbout{};
};
