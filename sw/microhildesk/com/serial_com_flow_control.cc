////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_flow_control.cc
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
/// @brief Converts FlowControl enum to numeric uint32_t.
/// @param flow FlowControl enumerator.
/// @return Numeric representation of flow control mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t SerialCom::flowControlToUint(const FlowControl flow)
{
	switch (flow)
	{
	case FlowControl::FLOW_CONTROL_NONE:
		return cComFlowControlNone;
	case FlowControl::FLOW_CONTROL_HARDWARE:
		return cComFlowControlHw;
	case FlowControl::FLOW_CONTROL_SOFTWARE:
		return cComFlowControlSw;
	case FlowControl::FLOW_CONTROL_INVALID:
	default:
		return cComInvalidParameter;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts numeric uint32_t to FlowControl enum.
/// @param flow Numeric representation of flow control mode.
/// @return Corresponding FlowControl enumerator or FLOW_CONTROL_INVALID if unsupported.
////////////////////////////////////////////////////////////////////////////////////////////////////////
FlowControl SerialCom::uintToFlowControl(const uint32_t flow)
{
	switch (flow)
	{
	case cComFlowControlNone:
		return FlowControl::FLOW_CONTROL_NONE;
	case cComFlowControlHw:
		return FlowControl::FLOW_CONTROL_HARDWARE;
	case cComFlowControlSw:
		return FlowControl::FLOW_CONTROL_SOFTWARE;
	default:
		return FlowControl::FLOW_CONTROL_INVALID;
	}
}
