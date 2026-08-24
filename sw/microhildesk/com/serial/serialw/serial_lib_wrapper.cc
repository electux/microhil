////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_lib_wrapper.cc
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

#include <com/serial/serialw/serial_lib_wrapper.h>
#include <memory>
#include <string>
#include <vector>

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructs a LibSerialPortWrapper object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
LibSerialPortWrapper::LibSerialPortWrapper()
    : m_serialPort(std::make_unique<LibSerial::SerialPort>()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destroys the LibSerialPortWrapper object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
LibSerialPortWrapper::~LibSerialPortWrapper() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the serial port with the specified device.
/// @param device The name of the device to open.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Open(const std::string &device) {
    m_serialPort->Open(device);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Closes the serial port.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Close() { m_serialPort->Close(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the serial port is open.
/// @return True if the serial port is open, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LibSerialPortWrapper::IsOpen() const { return m_serialPort->IsOpen(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from the serial port.
/// @param data A vector to store the read data.
/// @param len The number of bytes to read.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Read(std::vector<uint8_t> &data, size_t len) {
    m_serialPort->Read(data, len);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Writes data to the serial port.
/// @param data The data to write.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Write(const std::vector<uint8_t> &data) {
    m_serialPort->Write(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the baud rate of the serial port.
/// @param baudRate The baud rate to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetBaudRate(BaudRate baudRate) {
    LibSerial::BaudRate libBaud = LibSerial::BaudRate::BAUD_INVALID;
    switch (baudRate) {
    case BaudRate::BAUD_110:
        libBaud = LibSerial::BaudRate::BAUD_110;
        break;
    case BaudRate::BAUD_300:
        libBaud = LibSerial::BaudRate::BAUD_300;
        break;
    case BaudRate::BAUD_600:
        libBaud = LibSerial::BaudRate::BAUD_600;
        break;
    case BaudRate::BAUD_1200:
        libBaud = LibSerial::BaudRate::BAUD_1200;
        break;
    case BaudRate::BAUD_2400:
        libBaud = LibSerial::BaudRate::BAUD_2400;
        break;
    case BaudRate::BAUD_4800:
        libBaud = LibSerial::BaudRate::BAUD_4800;
        break;
    case BaudRate::BAUD_9600:
        libBaud = LibSerial::BaudRate::BAUD_9600;
        break;
    case BaudRate::BAUD_19200:
        libBaud = LibSerial::BaudRate::BAUD_19200;
        break;
    case BaudRate::BAUD_38400:
        libBaud = LibSerial::BaudRate::BAUD_38400;
        break;
    case BaudRate::BAUD_57600:
        libBaud = LibSerial::BaudRate::BAUD_57600;
        break;
    case BaudRate::BAUD_115200:
        libBaud = LibSerial::BaudRate::BAUD_115200;
        break;
    case BaudRate::BAUD_230400:
        libBaud = LibSerial::BaudRate::BAUD_230400;
        break;
    default:
        break;
    }
    m_serialPort->SetBaudRate(libBaud);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the character size of the serial port.
/// @param characterSize The character size to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetCharacterSize(CharacterSize characterSize) {
    LibSerial::CharacterSize libSize =
        LibSerial::CharacterSize::CHAR_SIZE_INVALID;
    switch (characterSize) {
    case CharacterSize::CHAR_SIZE_5:
        libSize = LibSerial::CharacterSize::CHAR_SIZE_5;
        break;
    case CharacterSize::CHAR_SIZE_6:
        libSize = LibSerial::CharacterSize::CHAR_SIZE_6;
        break;
    case CharacterSize::CHAR_SIZE_7:
        libSize = LibSerial::CharacterSize::CHAR_SIZE_7;
        break;
    case CharacterSize::CHAR_SIZE_8:
        libSize = LibSerial::CharacterSize::CHAR_SIZE_8;
        break;
    default:
        break;
    }
    m_serialPort->SetCharacterSize(libSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the parity of the serial port.
/// @param parity The parity to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetParity(Parity parity) {
    LibSerial::Parity libParity = LibSerial::Parity::PARITY_INVALID;
    switch (parity) {
    case Parity::PARITY_NONE:
        libParity = LibSerial::Parity::PARITY_NONE;
        break;
    case Parity::PARITY_ODD:
        libParity = LibSerial::Parity::PARITY_ODD;
        break;
    case Parity::PARITY_EVEN:
        libParity = LibSerial::Parity::PARITY_EVEN;
        break;
    default:
        break;
    }
    m_serialPort->SetParity(libParity);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the stop bits of the serial port.
/// @param stopBits The stop bits to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetStopBits(StopBits stopBits) {
    LibSerial::StopBits libStop = LibSerial::StopBits::STOP_BITS_INVALID;
    switch (stopBits) {
    case StopBits::STOP_BITS_1:
        libStop = LibSerial::StopBits::STOP_BITS_1;
        break;
    case StopBits::STOP_BITS_2:
        libStop = LibSerial::StopBits::STOP_BITS_2;
        break;
    default:
        break;
    }
    m_serialPort->SetStopBits(libStop);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the flow control of the serial port.
/// @param flowControl The flow control to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetFlowControl(FlowControl flowControl) {
    LibSerial::FlowControl libFlow =
        LibSerial::FlowControl::FLOW_CONTROL_INVALID;
    switch (flowControl) {
    case FlowControl::FLOW_CONTROL_NONE:
        libFlow = LibSerial::FlowControl::FLOW_CONTROL_NONE;
        break;
    case FlowControl::FLOW_CONTROL_SOFTWARE:
        libFlow = LibSerial::FlowControl::FLOW_CONTROL_SOFTWARE;
        break;
    case FlowControl::FLOW_CONTROL_HARDWARE:
        libFlow = LibSerial::FlowControl::FLOW_CONTROL_HARDWARE;
        break;
    default:
        break;
    }
    m_serialPort->SetFlowControl(libFlow);
}
