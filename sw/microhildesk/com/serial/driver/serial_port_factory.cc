////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_port_factory.cc
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

#include <com/serial/driver/serial_port_factory.h>
#include <com/serial/driver/posix_serial_port.h>

namespace Electux::App::Com {
    std::unique_ptr<ISerialPort> createPosixSerialPort(
        std::unique_ptr<ISerialTermiosConfigurator> termiosConfigurator
    ) {
        return std::make_unique<PosixSerialPort>(std::move(termiosConfigurator));
    }
} // namespace Electux::App::Com
