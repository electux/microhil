/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view.h
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
#include "home/microhil_view_home.h"
#include "microhil_view_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILView class declaration and definition 
class MicroHILView: public AbMicroHILView
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILView constructor
    MicroHILView();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILView destructor
    ~MicroHILView() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting home view
    /// @return home view instance
    Glib::RefPtr<MicroHILViewHome> getHome();

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_builder{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Home view instance
    Glib::RefPtr<MicroHILViewHome> m_home{nullptr};
};
