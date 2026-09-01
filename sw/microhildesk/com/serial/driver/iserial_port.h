////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iserial_port.h
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <com/serial/driver/serial_port_types.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ISerialPort
    /// @brief Abstract interface representing a low-level serial port device.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ISerialPort {
      public:
        virtual ~ISerialPort() = default;

        virtual void Open(const std::string &device) = 0;
        virtual void Close() = 0;
        virtual bool IsOpen() const = 0;

        virtual void Read(std::vector<uint8_t> &data, size_t len) = 0;
        virtual void Write(const std::vector<uint8_t> &data) = 0;

        virtual void SetBaudRate(BaudRate baudRate) = 0;
        virtual void SetCharacterSize(CharacterSize characterSize) = 0;
        virtual void SetParity(Parity parity) = 0;
        virtual void SetStopBits(StopBits stopBits) = 0;
        virtual void SetFlowControl(FlowControl flowControl) = 0;
    };

    using ILibSerialPort = ISerialPort;
} // namespace Electux::App::Com
