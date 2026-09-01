////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iserial_termios_configurator.h
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

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ISerialTermiosConfigurator
    /// @brief Abstract interface for configuring Linux POSIX termios terminal attributes.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ISerialTermiosConfigurator {
      public:
        virtual ~ISerialTermiosConfigurator() = default;

        virtual void configureRawMode(int fd) = 0;
        virtual void setBaudRate(int fd, BaudRate baudRate) = 0;
        virtual void setCharacterSize(int fd, CharacterSize characterSize) = 0;
        virtual void setParity(int fd, Parity parity) = 0;
        virtual void setStopBits(int fd, StopBits stopBits) = 0;
        virtual void setFlowControl(int fd, FlowControl flowControl) = 0;
    };
} // namespace Electux::App::Com
