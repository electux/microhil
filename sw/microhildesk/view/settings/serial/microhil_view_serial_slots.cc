/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial_slots.cc
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

void MicroHILViewSerial::onSerialFilePathChanged()
{
    // TODO
}

void MicroHILViewSerial::onSerialBaudRateChanged()
{
    // TODO
}

void MicroHILViewSerial::onSerialDataBitsChanged()
{
    // TODO
}

void MicroHILViewSerial::onSerialParityChanged()
{
    // TODO
}

void MicroHILViewSerial::onSerialStopBitsChanged()
{
    // TODO
}

void MicroHILViewSerial::onCancelSerialTriggered()
{
    this->hide();
}

void MicroHILViewSerial::onOkSerialTriggered()
{
    auto devicePath = m_device->get_text();

    VectorUInt serialParams{};
    serialParams.push_back(m_baudRate->get_active_row_number());
    serialParams.push_back(m_dataBits->get_active_row_number());
    serialParams.push_back(m_parity->get_active_row_number());
    serialParams.push_back(m_stopBits->get_active_row_number());

    ////////////////////////////////////////////////////////////////////////
    /// Emit new serial settings
    m_serialSetup.emit(devicePath, serialParams);

    this->hide();
}
