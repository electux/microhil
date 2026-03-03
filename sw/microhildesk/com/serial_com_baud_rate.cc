////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_baud_rate.cc
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
#include <params/serial_com_params.h>

using namespace Electux::App::Com;
using namespace Electux::App::Params::SerialComConstants;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts BaudRate enum to numeric uint32_t.
/// @param baud Scoped enumerator value representing baud rate.
/// @return Numeric representation or cComInvalidParameter if unsupported.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t SerialCom::baudToUint(const BaudRate baud)
{
	switch (baud)
	{
	case BaudRate::BAUD_50:
		return cComInvalidParameter;
	case BaudRate::BAUD_75:
		return cComInvalidParameter;
	case BaudRate::BAUD_110:
		return cComBaud110;
	case BaudRate::BAUD_134:
		return cComInvalidParameter;
	case BaudRate::BAUD_150:
		return cComInvalidParameter;
	case BaudRate::BAUD_200:
		return cComInvalidParameter;
	case BaudRate::BAUD_300:
		return cComBaud300;
	case BaudRate::BAUD_600:
		return cComBaud600;
	case BaudRate::BAUD_1200:
		return cComBaud1200;
	case BaudRate::BAUD_1800:
		return cComInvalidParameter;
	case BaudRate::BAUD_2400:
		return cComBaud2400;
	case BaudRate::BAUD_4800:
		return cComBaud4800;
	case BaudRate::BAUD_9600:
		return cComBaud9600;
	case BaudRate::BAUD_19200:
		return cComBaud19200;
	case BaudRate::BAUD_38400:
		return cComBaud38400;
	case BaudRate::BAUD_57600:
		return cComBaud57600;
	case BaudRate::BAUD_115200:
		return cComBaud115200;
	case BaudRate::BAUD_230400:
		return cComBaud230400;
	case BaudRate::BAUD_460800:
		return cComInvalidParameter;
	case BaudRate::BAUD_500000:
		return cComInvalidParameter;
	case BaudRate::BAUD_576000:
		return cComInvalidParameter;
	case BaudRate::BAUD_921600:
		return cComInvalidParameter;
	case BaudRate::BAUD_1000000:
		return cComInvalidParameter;
	case BaudRate::BAUD_1152000:
		return cComInvalidParameter;
	case BaudRate::BAUD_1500000:
		return cComInvalidParameter;
	case BaudRate::BAUD_2000000:
		return cComInvalidParameter;
	case BaudRate::BAUD_2500000:
		return cComInvalidParameter;
	case BaudRate::BAUD_3000000:
		return cComInvalidParameter;
	case BaudRate::BAUD_3500000:
		return cComInvalidParameter;
	case BaudRate::BAUD_4000000:
		return cComInvalidParameter;
	default:
		return cComInvalidParameter;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts numeric uint32_t to BaudRate enum.
/// @param baud Numeric value representing baud rate.
/// @return BaudRate enumerator or BAUD_INVALID if mapping fails.
////////////////////////////////////////////////////////////////////////////////////////////////////////
BaudRate SerialCom::uintToBaud(const uint32_t baud)
{
	switch (baud)
	{
	case cComBaud110:
		return BaudRate::BAUD_110;
	case cComBaud300:
		return BaudRate::BAUD_300;
	case cComBaud600:
		return BaudRate::BAUD_600;
	case cComBaud1200:
		return BaudRate::BAUD_1200;
	case cComBaud2400:
		return BaudRate::BAUD_2400;
	case cComBaud4800:
		return BaudRate::BAUD_4800;
	case cComBaud9600:
		return BaudRate::BAUD_9600;
	case cComBaud19200:
		return BaudRate::BAUD_19200;
	case cComBaud38400:
		return BaudRate::BAUD_38400;
	case cComBaud57600:
		return BaudRate::BAUD_57600;
	case cComBaud115200:
		return BaudRate::BAUD_115200;
	case cComBaud230400:
		return BaudRate::BAUD_230400;
	}

	return BaudRate::BAUD_INVALID;
}
