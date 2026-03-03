////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_data_bits.cc
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
/// @brief Converts CharacterSize enum to numeric uint32_t.
/// @param data CharacterSize enumerator.
/// @return Numeric representation of data bits.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t SerialCom::dataBitsToUint(const CharacterSize data)
{
	switch (data)
	{
	case CharacterSize::CHAR_SIZE_5:
		return cComDataBits5;
	case CharacterSize::CHAR_SIZE_6:
		return cComDataBits6;
	case CharacterSize::CHAR_SIZE_7:
		return cComDataBits7;
	case CharacterSize::CHAR_SIZE_8:
		return cComDataBits8;
	default:
		return cComInvalidParameter;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts numeric uint32_t to CharacterSize enum.
/// @param data Numeric representation of data bits.
/// @return CharacterSize enumerator or CHAR_SIZE_INVALID if unsupported.
////////////////////////////////////////////////////////////////////////////////////////////////////////
CharacterSize SerialCom::uintToDataBits(const uint32_t data)
{
    switch (data)
    {
    case cComDataBits5:
        return CharacterSize::CHAR_SIZE_5;
    case cComDataBits6:
        return CharacterSize::CHAR_SIZE_6;
    case cComDataBits7:
        return CharacterSize::CHAR_SIZE_7;
    case cComDataBits8:
        return CharacterSize::CHAR_SIZE_8;
    }

    return CharacterSize::CHAR_SIZE_INVALID;
}
