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

MicroHILSerialCom::MicroHILSerialCom()
{
    m_serialPort = make_unique<SerialPort>();
}

MicroHILSerialCom::~MicroHILSerialCom()
{
    close();
}

void MicroHILSerialCom::open()
{
    if(!m_serialPort->IsOpen())
    {
        m_serialPort->Open(std::string(m_device));
    }
}

void MicroHILSerialCom::close()
{
    if(m_serialPort->IsOpen())
    {
        m_serialPort->Close();
    }
}

void MicroHILSerialCom::setup(
    Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
    unsigned int parity, unsigned int stopBits
)
{
    m_serialPort->SetBaudRate(static_cast<BaudRate>(baudRate));
    m_serialPort->SetCharacterSize(static_cast<CharacterSize>(dataBits));
    m_serialPort->SetParity(static_cast<Parity>(parity));
    m_serialPort->SetStopBits(static_cast<StopBits>(stopBits));
    m_device = device;
}

void MicroHILSerialCom::setup(
    Glib::ustring device, BaudRate baudRate, CharacterSize dataBits,
    Parity parity, StopBits stopBits
)
{
    m_serialPort->SetBaudRate(baudRate);
    m_serialPort->SetCharacterSize(dataBits);
    m_serialPort->SetParity(parity);
    m_serialPort->SetStopBits(stopBits);
    m_device = device;
}

void MicroHILSerialCom::read(v_uint8 &data, size_t len, size_t timeout)
{
}

void MicroHILSerialCom::write(v_uint8& data)
{
}
