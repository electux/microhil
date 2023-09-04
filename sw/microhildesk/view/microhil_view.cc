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
    /// Resource path for Home UI
    constexpr char kHomeUI[]{"/org/gtkmm/microhildesk/microhil.ui"};

    ////////////////////////////////////////////////////////////////////////
    /// Application Window ID
    constexpr char kWindowId[]{"Window"};

    ////////////////////////////////////////////////////////////////////////
    /// Application Dialog ID
    constexpr char kDialogId[]{"DialogMessage"};

    ////////////////////////////////////////////////////////////////////////
    /// Application Log Settings ID
    constexpr char kLogId[]{"LogDialog"};

    ////////////////////////////////////////////////////////////////////////
    /// Application Serial Settings ID
    constexpr char kSerialId[]{"SerialDialog"};

    ////////////////////////////////////////////////////////////////////////
    /// Application About ID
    constexpr char kAboutId[]{"AboutDialog"};
}

MicroHILView::MicroHILView():
    m_builder{Gtk::Builder::create_from_resource(kHomeUI)}
{
    ////////////////////////////////////////////////////////////////////////
    /// Setup builder and home view
    m_builder->get_widget_derived(kWindowId, (MicroHILViewHome*&)m_home);

    ////////////////////////////////////////////////////////////////////////
    /// Setup builder and dialog view
    m_builder->get_widget_derived(kDialogId, (MicroHILViewDialog*&)m_dialog);

    ////////////////////////////////////////////////////////////////////////
    /// Setup builder and Log Settings view
    m_builder->get_widget_derived(kLogId, (MicroHILViewLog*&)m_log);

    ////////////////////////////////////////////////////////////////////////
    /// Setup builder and Serial Settings view
    m_builder->get_widget_derived(kSerialId, (MicroHILViewSerial*&)m_serial);

    ////////////////////////////////////////////////////////////////////////
    /// Setup builder and About view
    m_builder->get_widget_derived(kAboutId, (MicroHILViewAbout*&)m_about);

    ////////////////////////////////////////////////////////////////////////
    /// Mapping views (signals and slots)
    mapping();
}

MHRPtr<MicroHILViewHome> MicroHILView::getHome()
{
    return m_home;
}

MHRPtr<MicroHILViewLog> MicroHILView::getLogSettings()
{
    return m_log;
}

MHRPtr<MicroHILViewSerial> MicroHILView::getSerialSettings()
{
    return m_serial;
}
