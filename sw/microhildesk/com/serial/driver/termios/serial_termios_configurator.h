////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_termios_configurator.h
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

#include <com/serial/driver/termios/iserial_termios_configurator.h>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class SerialTermiosConfigurator
    /// @brief Concrete implementation of ISerialTermiosConfigurator for Linux POSIX termios.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class SerialTermiosConfigurator : public ISerialTermiosConfigurator {
      public:
        SerialTermiosConfigurator() = default;
        ~SerialTermiosConfigurator() override = default;

        SerialTermiosConfigurator(const SerialTermiosConfigurator &) = delete;
        SerialTermiosConfigurator &operator=(const SerialTermiosConfigurator &) = delete;

        void configureRawMode(int fd) override;
        void setBaudRate(int fd, BaudRate baudRate) override;
        void setCharacterSize(int fd, CharacterSize characterSize) override;
        void setParity(int fd, Parity parity) override;
        void setStopBits(int fd, StopBits stopBits) override;
        void setFlowControl(int fd, FlowControl flowControl) override;
    };
} // namespace Electux::App::Com
