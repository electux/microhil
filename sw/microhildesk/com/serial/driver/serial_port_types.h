////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_port_types.h
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

#include <cstdint>
#include <stdexcept>
#include <string>

namespace Electux::App::Com {
    enum class BaudRate : uint32_t {
        BAUD_INVALID = 0,
        BAUD_110,
        BAUD_300,
        BAUD_600,
        BAUD_1200,
        BAUD_2400,
        BAUD_4800,
        BAUD_9600,
        BAUD_19200,
        BAUD_38400,
        BAUD_57600,
        BAUD_115200,
        BAUD_230400
    };

    enum class CharacterSize : uint8_t {
        CHAR_SIZE_INVALID = 0,
        CHAR_SIZE_5,
        CHAR_SIZE_6,
        CHAR_SIZE_7,
        CHAR_SIZE_8
    };

    enum class Parity : uint8_t {
        PARITY_INVALID = 0,
        PARITY_NONE,
        PARITY_ODD,
        PARITY_EVEN
    };

    enum class StopBits : uint8_t {
        STOP_BITS_INVALID = 0,
        STOP_BITS_1,
        STOP_BITS_2
    };

    enum class FlowControl : uint8_t {
        FLOW_CONTROL_INVALID = 0,
        FLOW_CONTROL_NONE,
        FLOW_CONTROL_SOFTWARE,
        FLOW_CONTROL_HARDWARE
    };

    class SerialReadTimeout : public std::runtime_error {
      public:
        explicit SerialReadTimeout(const std::string &message)
            : std::runtime_error(message) {}
    };

    class SerialNotOpen : public std::runtime_error {
      public:
        explicit SerialNotOpen(const std::string &message)
            : std::runtime_error(message) {}
    };
} // namespace Electux::App::Com

namespace LibSerial {
    using ReadTimeout = Electux::App::Com::SerialReadTimeout;
    using NotOpen = Electux::App::Com::SerialNotOpen;
} // namespace LibSerial
