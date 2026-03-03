////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_setup.cc
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
/// @brief Configures the serial port with specific parameters.
/// @param params Reference to SerialParams structure (configuration).
/// @return True if setup was successful, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::setup(const SerialParams &params)
{
    try
    {
        setBaudRate(params.baud);
        setCharacterSize(params.data);
        setParity(params.parity);
        setStopBits(params.stop);
        setFlowControl(params.flow);
        m_device = params.device;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Setup error: " << e.what() << std::endl;
        return false;
    }
}
