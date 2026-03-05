////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_iserial.h
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
#pragma once

#include <gmock/gmock.h>
#include <com/iserial.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace com::mock
/// @brief Namespace for application communication mocks
namespace com::mock
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Local Type Aliases
	/// @{
    using ISerial = Electux::App::Com::ISerial;
    using SerialParams = Electux::App::Com::SerialParams;
    using BaudRate = Electux::App::Com::BaudRate;
    using CharacterSize = Electux::App::Com::CharacterSize;
    using Parity = Electux::App::Com::Parity;
    using StopBits = Electux::App::Com::StopBits;
    using FlowControl = Electux::App::Com::FlowControl;
    /// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class MockISerial
    /// @brief Mock implementation of the ISerial interface for testing purposes.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class MockISerial : public ISerial
    {
    public:
        MOCK_METHOD(bool, setup, (const SerialParams &params), (override));
        MOCK_METHOD(void, setDevice, (const std::string &device), (override));
        MOCK_METHOD(void, setBaudRate, (BaudRate baudRate), (override));
        MOCK_METHOD(void, setCharacterSize, (CharacterSize characterSize), (override));
        MOCK_METHOD(void, setParity, (Parity parity), (override));
        MOCK_METHOD(void, setStopBits, (StopBits stopBits), (override));
        MOCK_METHOD(void, setFlowControl, (FlowControl flowControl), (override));
        MOCK_METHOD(uint32_t, baudToUint, (const BaudRate baud), (override));
        MOCK_METHOD(BaudRate, uintToBaud, (const uint32_t baud), (override));
        MOCK_METHOD(uint32_t, dataBitsToUint, (const CharacterSize data), (override));
        MOCK_METHOD(CharacterSize, uintToDataBits, (const uint32_t data), (override));
        MOCK_METHOD(uint32_t, parityToUint, (const Parity parity), (override));
        MOCK_METHOD(Parity, uintToParity, (const uint32_t parity), (override));
        MOCK_METHOD(uint32_t, stopBitsToUint, (const StopBits stop), (override));
        MOCK_METHOD(StopBits, uintToStopBits, (const uint32_t stop), (override));
        MOCK_METHOD(uint32_t, flowControlToUint, (const FlowControl flow), (override));
        MOCK_METHOD(FlowControl, uintToFlowControl, (const uint32_t flow), (override));
    };
} // namespace com::mock
