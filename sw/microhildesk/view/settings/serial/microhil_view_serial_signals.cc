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

MHViewSerial::SigSerialSetup MHViewSerial::serialSetupChanged()
{
    return m_serialSetup;
}

MHViewSerial::SigSerialDevicePath MHViewSerial::serialFilePathChanged()
{
    return m_serialDevicePath;
}

MHViewSerial::SigSerialBaudRate MHViewSerial::serialBaudRateChanged()
{
    return m_serialBaudeRate;
}

MHViewSerial::SigSerialDataBits MHViewSerial::serialDataBitsChanged()
{
    return m_serialDataBits;
}

MHViewSerial::SigSerialParity MHViewSerial::serialParityChanged()
{
    return m_serialParity;
}

MHViewSerial::SigSerialStopBits MHViewSerial::serialStopBitsChanged()
{
    return m_serialStopBits;
}

MHViewSerial::SigCancelSerial MHViewSerial::cancelSerialTriggered()
{
    return m_cancelSerial;
}

MHViewSerial::SigOkSerial MHViewSerial::okSerialTriggered()
{
    return m_okSerial;
}
