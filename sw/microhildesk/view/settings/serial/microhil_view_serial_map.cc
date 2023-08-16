/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial_map.cc
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
#include "microhil_view_serial.h"

void MicroHILViewSerial::mapping()
{
    ////////////////////////////////////////////////////////////////////////
    // Map signals and slots
    m_device->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onserialFilePathChange)
    );

    m_baudRate->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onSerialBaudRateChange)
    );

    m_dataBits->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onSerialDataBitsChange)
    );

    m_parity->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onSerialParityChange)
    );

    m_stopBits->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onSerialStopBitsChange)
    );

    m_cancel->signal_clicked().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onCancelSerialChange)
    );

    m_ok->signal_clicked().connect(
        sigc::mem_fun(*this, &MicroHILViewSerial::onOkSerialChange)
    );
}
