////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_parity.cc
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
/// @brief Converts Parity enum to numeric uint32_t.
/// @param parity Parity enumerator.
/// @return Numeric representation of parity mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t SerialCom::parityToUint(const Parity parity)
{
	switch (parity)
	{
	case Parity::PARITY_EVEN:
		return cComParityEven;
	case Parity::PARITY_ODD:
		return cComParityOdd;
	case Parity::PARITY_NONE:
		return cComParityNone;
	case Parity::PARITY_INVALID:
		return cComInvalidParameter;
	}

	return cComInvalidParameter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts numeric uint32_t to Parity enum.
/// @param parity Numeric format of parity.
/// @return Parity enumerator or PARITY_INVALID.
////////////////////////////////////////////////////////////////////////////////////////////////////////
Parity SerialCom::uintToParity(const uint32_t parity)
{
	switch (parity)
	{
	case cComParityEven:
		return Parity::PARITY_EVEN;
	case cComParityOdd:
		return Parity::PARITY_ODD;
	case cComParityNone:
		return Parity::PARITY_NONE;
	}

	return Parity::PARITY_INVALID;
}
