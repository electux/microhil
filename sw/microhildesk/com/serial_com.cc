////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <com/serial_com.h>
#include <iostream>

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructs a SerialCom object with the given serial port adapter.
/// @param port A unique pointer to an ILibSerialPort implementation.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SerialCom::SerialCom(std::unique_ptr<ILibSerialPort> port)
    : m_serialPort(std::move(port))
{
    std::cout << "SerialCom constructor called." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destructor for the SerialCom class. Ensures the serial port is closed.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SerialCom::~SerialCom() noexcept
{
    if (!close())
    {
        std::cerr << "Close error: Serial port was not closed properly." << std::endl;
    }

    std::cout << "SerialCom destructor called." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the serial port.
/// @return True if the port was successfully opened, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::open()
{
    if (m_device.empty())
    {
        std::cerr << "Open error: Device path is empty!" << std::endl;
        return false;
    }

    if (!isOpen())
    {
        try
        {
            m_serialPort->Open(m_device);
            std::cout << "Serial port opened successfully." << std::endl;
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Open error: " << e.what() << std::endl;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Closes the serial port.
/// @return True if the port was successfully closed, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::close()
{
    if (isOpen())
    {
        m_serialPort->Close();
        std::cout << "Serial port closed successfully." << std::endl;
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the serial port is open.
/// @return True if the port is open, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::isOpen() const
{
    bool open = m_serialPort->IsOpen();
    std::cout << "Serial port is " << (open ? "open." : "closed.") << std::endl;
    return open;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from the serial port.
/// @param data A vector to store the read data.
/// @param len The number of bytes to read.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::read(std::vector<uint8_t> &data, size_t len)
{
    if (!isOpen())
    {
        std::cerr << "Read error: Serial port closed." << std::endl;
        return;
    }

    m_serialPort->Read(data, len);
    std::cout << "Read " << data.size() << " bytes from serial port." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Writes data to the serial port.
/// @param data A vector containing the data to write.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::write(const std::vector<uint8_t> &data)
{
    if (!isOpen())
    {
        std::cerr << "Write error: Serial port closed." << std::endl;
        return;
    }

    m_serialPort->Write(data);
    std::cout << "Wrote " << data.size() << " bytes to serial port." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the baud rate for the serial port.
/// @param baudRate The desired baud rate.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setBaudRate(BaudRate baudRate)
{
    m_serialPort->SetBaudRate(baudRate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the character size for the serial port.
/// @param characterSize The desired character size.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setCharacterSize(CharacterSize characterSize)
{
    m_serialPort->SetCharacterSize(characterSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the parity mode for the serial port.
/// @param parity The desired parity mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setParity(Parity parity)
{
    m_serialPort->SetParity(parity);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the number of stop bits for the serial port.
/// @param stopBits The desired number of stop bits.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setStopBits(StopBits stopBits)
{
    m_serialPort->SetStopBits(stopBits);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the flow control mode for the serial port.
/// @param flowControl The desired flow control mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setFlowControl(FlowControl flowControl)
{
    m_serialPort->SetFlowControl(flowControl);
}
