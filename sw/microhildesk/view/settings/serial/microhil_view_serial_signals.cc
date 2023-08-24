/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_serial_signals.cc
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

MicroHILViewSerial::serialSetup
MicroHILViewSerial::serialSetupChanged()
{
    return m_serialSetup;
}

MicroHILViewSerial::serialDevicePath
MicroHILViewSerial::serialFilePathChanged()
{
    return m_serialDevicePath;
}

MicroHILViewSerial::serialBaudRate
MicroHILViewSerial::serialBaudRateChanged()
{
    return m_serialBaudeRate;
}

MicroHILViewSerial::serialDataBits
MicroHILViewSerial::serialDataBitsChanged()
{
    return m_serialDataBits;
}

MicroHILViewSerial::serialParity
MicroHILViewSerial::serialParityChanged()
{
    return m_serialParity;
}

MicroHILViewSerial::serialStopBits
MicroHILViewSerial::serialStopBitsChanged()
{
    return m_serialStopBits;
}

MicroHILViewSerial::cancelSerial
MicroHILViewSerial::cancelSerialTriggered()
{
    return m_cancelSerial;
}

MicroHILViewSerial::okSerial
MicroHILViewSerial::okSerialTriggered()
{
    return m_okSerial;
}
