////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_stop_bits.cc
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
/// @brief Converts StopBits enum to numeric uint32_t.
/// @param stop StopBits enumerator.
/// @return Numeric representation of stop bits.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t SerialCom::stopBitsToUint(const StopBits stop)
{
	switch (stop)
	{
	case StopBits::STOP_BITS_1:
		return cComStopBits1;
	case StopBits::STOP_BITS_2:
		return cComStopBits2;
	case StopBits::STOP_BITS_INVALID:
		return cComInvalidParameter;
	}

	return cComInvalidParameter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts numeric uint32_t to StopBits enum.
/// @param stop Numeric format of stop bits.
/// @return StopBits enumerator or STOP_BITS_INVALID.
////////////////////////////////////////////////////////////////////////////////////////////////////////
StopBits SerialCom::uintToStopBits(const uint32_t stop)
{
	switch (stop)
	{
	case cComStopBits1:
		return StopBits::STOP_BITS_1;
	case cComStopBits2:
		return StopBits::STOP_BITS_2;
	}

	return StopBits::STOP_BITS_INVALID;
}
