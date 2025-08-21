/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com.cc
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "serial_com.h"

using namespace Electux::App::Com;

SerialCom::SerialCom(): m_serialPort{SerialPort()}
{
    close();
}

void SerialCom::open()
{
    if (!m_serialPort.IsOpen())
    {
        m_serialPort.Open(std::string(m_device));
    }
}

void SerialCom::close()
{
    if (m_serialPort.IsOpen())
    {
        m_serialPort.Close();
    }
}

void SerialCom::setup(const SerialParams &params)
{
    if (m_serialPort.IsOpen())
    {
        m_serialPort.Close();
    }

    ////////////////////////////////////////////////////////////////////////
    /// Sets serial port device path
    m_device = params.device;

    open();

    ////////////////////////////////////////////////////////////////////////
    /// Sets serial port parameters
    m_serialPort.SetBaudRate(params.baud);
    m_serialPort.SetCharacterSize(params.data);
    m_serialPort.SetParity(params.parity);
    m_serialPort.SetStopBits(params.stop);
}

void SerialCom::read(std::vector<uint8_t> &data, size_t len)
{
    m_serialPort.Read(data, len);
}

void SerialCom::write(const std::vector<uint8_t> &data)
{
    m_serialPort.Write(data);
}

