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

void MHView::onViewChanged(ViewId id)
{
    switch (static_cast<int>(id))
    {
    case static_cast<int>(ViewId::MICROHIL_CONNECT):
        ////////////////////////////////////////////////////////////////////
        /// Enables and opens the serial port
        m_serialPortChanged.emit(true);
        break;
    case static_cast<int>(ViewId::MICROHIL_DISCONNECT):
        ////////////////////////////////////////////////////////////////////
        /// Disables and closes the serial port
        m_serialPortChanged.emit(false);
        break;
    case static_cast<int>(ViewId::MICROHIL_QUIT):
        break;
    case static_cast<int>(ViewId::MICROHIL_SERIAL_SETTINGS):
        ////////////////////////////////////////////////////////////////////
        /// Activate serial settings view
        m_serial->show();
        break;
    case static_cast<int>(ViewId::MICROHIL_LOG_SETTINGS):
        ////////////////////////////////////////////////////////////////////
        /// Activate log settings view
        m_log->show();
        break;
    case static_cast<int>(ViewId::MICROHIL_ABOUT):
        ////////////////////////////////////////////////////////////////////
        /// Activate about view
        m_about->show();
        break;
    }
}

void MHView::onConfirmSerialSettings(bool state)
{
    m_home->serialSettingsConfirm(state);
}
