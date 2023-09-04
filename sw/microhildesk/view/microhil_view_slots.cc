/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_slots.cc
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

void MicroHILView::onViewChanged(ViewId id)
{
    int viewId = static_cast<int>(id);

    switch(viewId)
    {
        case static_cast<int>(ViewId::MICROHIL_SERIAL_SETTINGS):
            m_serial->show();
            break;
        case static_cast<int>(ViewId::MICROHIL_LOG_SETTINGS):
            m_log->show();
            break;
        case static_cast<int>(ViewId::MICROHIL_ABOUT):
            m_about->show();
            break;
    }
}
