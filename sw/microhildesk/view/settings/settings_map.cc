/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_map.cc
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "settings.h"

using namespace Electux::App::View::Settings;

void AppSettings::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// Maps the signal handlers to the buttons
    m_button_ok.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::on_button_ok_clicked)
    );
    m_button_cancel.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::on_button_cancel_clicked)
    );
}
