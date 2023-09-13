/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_serial_com.cc
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
#include "microhil_serial_com.h"

MHSerialCom::MHSerialCom() : m_serialPort{MHmakeUPtr<SerialPort>()}
{
    close();
}

MHSerialCom::~MHSerialCom()
{
    close();
}

void MHSerialCom::open()
{
    if (!m_serialPort->IsOpen())
    {
        m_serialPort->Open(std::string(m_device));
    }
}

void MHSerialCom::close()
{
    if (m_serialPort->IsOpen())
    {
        m_serialPort->Close();
    }
}

void MHSerialCom::setup(MHString device, MHVecUInt params)
{
    m_serialPort->SetBaudRate(uintToBaudRate(params[0]));
    m_serialPort->SetCharacterSize(uintToDataBits(params[1]));
    m_serialPort->SetParity(uintToParity(params[2]));
    m_serialPort->SetStopBits(uintToStopBits(params[3]));
    m_device = device;
}

void MHSerialCom::setup(MHString device, MHSerialParams params)
{
    m_serialPort->SetBaudRate(params.baudRate);
    m_serialPort->SetCharacterSize(params.dataBits);
    m_serialPort->SetParity(params.parity);
    m_serialPort->SetStopBits(params.stopBits);
    m_device = device;
}

void MHSerialCom::read(MHVecByte &data, size_t len, size_t timeout)
{
    m_serialPort->Read(data, len, timeout);
}

void MHSerialCom::write(MHVecByte &data)
{
    m_serialPort->Write(data);
}
