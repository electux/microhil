/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view.cc
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
#include "microhil_view.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Resource path for home UI
    constexpr char kHomeUI[]{"/org/gtkmm/microhildesk/home.ui"};
    
    ////////////////////////////////////////////////////////////////////////
    /// Application window ID
    constexpr char kwindowId[]{"Window"};
}

MicroHILView::MicroHILView()
{
    m_builder = Gtk::Builder::create_from_resource(kHomeUI);
    m_builder->get_widget_derived(kwindowId, (MicroHILViewHome*&) m_home);
}

Glib::RefPtr<MicroHILViewHome> MicroHILView::getHome()
{
    return m_home;
}
