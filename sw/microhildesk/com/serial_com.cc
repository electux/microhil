/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <iostream>
#include <com/serial_com.h>

using namespace Electux::App::Com;

SerialCom::~SerialCom() noexcept
{
    close();
}

void SerialCom::open()
{
    std::cout << "Open serial port..." << std::endl;

    if (m_device.empty())
    {
        std::cerr << "Error: Device path is empty!" << std::endl;
        return;
    }

    if (!m_serialPort.IsOpen())
    {
        try
        {
            m_serialPort.Open(std::string(m_device));
            std::cout << "Open serial port done." << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error opening serial port: " << e.what() << std::endl;
        }
    }
}

void SerialCom::close()
{
    std::cout << "Close serial port..." << std::endl;

    if (m_serialPort.IsOpen())
    {
        m_serialPort.Close();
        std::cout << "Close serial port done." << std::endl;
    }
}

void SerialCom::setup(const SerialParams &params)
{
    std::cout << "Setup serial port..." << std::endl;

    if (m_serialPort.IsOpen())
    {
        m_serialPort.Close();
    }

    try
    {
        ////////////////////////////////////////////////////////////////////
        /// @brief Sets serial port device path
        m_device = params.device;
        open();

        if (m_serialPort.IsOpen())
        {
            ////////////////////////////////////////////////////////////////
            /// @brief Sets serial port parameters
            m_serialPort.SetBaudRate(params.baud);
            m_serialPort.SetCharacterSize(params.data);
            m_serialPort.SetParity(params.parity);
            m_serialPort.SetStopBits(params.stop);
            m_serialPort.SetFlowControl(params.flow);

            std::cout << "Setup serial port done." << std::endl;
        }
        else 
        {
            std::cerr << "Error: Port could not be opened, skipping configuration." << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error setting up serial port: " << e.what() << std::endl;
    }
}

void SerialCom::read(std::vector<uint8_t> &data, size_t len)
{
    if (!m_serialPort.IsOpen()) {
        std::cerr << "Read error: Port closed." << std::endl;
        return;
    }

    if (len == 0)
    {
        return;
    }

    m_serialPort.Read(data, len);
}

void SerialCom::write(const std::vector<uint8_t> &data)
{
    if (!m_serialPort.IsOpen()) {
        std::cerr << "Write error: Port closed." << std::endl;
        return;
    }

    if (data.empty())
    {
        return;
    }

    m_serialPort.Write(data);
}

