/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_about.cc
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
#include "microhil_view_about.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Ok button id
    constexpr const char kOkButtonId[]{"AboutOk"};
}

MHViewAbout::MHViewAbout(
    BaseObjectType *object, MHRPtr<Gtk::Builder> const &ui
) : Gtk::AboutDialog(object), m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    /// Binds Ok button
    m_ok = MHRPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kOkButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Maps Ok button (signal and slot)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Hides About dialog by default
    this->hide();
}
