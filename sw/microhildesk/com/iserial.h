////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iserial.h
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

#include <string>
#include <cstdint>
#include <com/ilib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Com
/// @brief Namespace for application communication components
namespace Electux::App::Com
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct SerialParams
	/// @brief Configuration structure for serial port parameters.
	///
	/// This structure aggregates all necessary settings required to initialize
	/// and configure a serial communication session.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct SerialParams
	{
		std::string device;   ///< Path to the serial port device
		BaudRate baud;        ///< Transmission speed (Baud rate)
		CharacterSize data;   ///< Number of data bits per character
		Parity parity;        ///< Parity error-checking scheme
		StopBits stop;        ///< Number of stop bits to indicate end
		FlowControl flow;     ///< Hardware or software flow control method
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class ISerial
	/// @brief Interface for serial communication implementations.
	///
	/// Defines the contract for configuring serial port parameters and
    /// provides utility methods to convert between LibSerial enums and
    /// generic numeric types for easier configuration handling. 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ISerial
	{
	public:
    	////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Virtual destructor for the ISerial interface.
		/// Ensures proper resource cleanup in derived serial communication classes.
		////////////////////////////////////////////////////////////////////////////////////////////////
		inline virtual ~ISerial() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Configures the serial port with specific parameters.
		/// @param params Reference to SerialParams structure (configuration).
		/// @return True if setup was successful, false otherwise.
		/// Implementation should apply the provided settings to the underlying
		/// serial port, returning success status based on the outcome.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool setup(const SerialParams &params) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the baud rate for the serial port.
		/// @param baudRate The desired baud rate.
		/// Implementation should call the underlying serial port method to
		/// apply the baud rate setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setBaudRate(BaudRate baudRate) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the character size for the serial port.
		/// @param characterSize The desired character size.
		/// Implementation should call the underlying serial port method to
		/// apply the character size setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setCharacterSize(CharacterSize characterSize) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the parity mode for the serial port.
		/// @param parity The desired parity mode.
		/// Implementation should call the underlying serial port method to
		/// apply the parity setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setParity(Parity parity) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the number of stop bits for the serial port.
		/// @param stopBits The desired number of stop bits.
		/// Implementation should call the underlying serial port method to
		/// apply the stop bits setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setStopBits(StopBits stopBits) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the flow control mode for the serial port.
		/// @param flowControl The desired flow control mode.
		/// Implementation should call the underlying serial port method to
		/// apply the flow control setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setFlowControl(FlowControl flowControl) = 0;

    protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Utility Conversion Methods
		/// Internal helpers to bridge LibSerial enums and generic numeric types.
		/// @{

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts BaudRate enum to numeric uint32_t.
		/// @param baud Scoped enumerator value.
		/// @return Numeric representation of the baud rate.
		/// Implementation should map known BaudRate values to their
		/// corresponding integers (e.g., BaudRate::BAUD_9600 to 9600).
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual uint32_t baudToUint(const BaudRate baud) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts numeric uint32_t to BaudRate enum.
		/// @param baud Numeric value.
		/// @return Scoped enumerator for the baud rate.
		/// Implementation should map common baud rate integers to their
		/// corresponding BaudRate enums (e.g., 9600 to BaudRate::BAUD_9600).
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual BaudRate uintToBaud(const uint32_t baud) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts CharacterSize enum to numeric uint32_t.
		/// @param data Scoped enumerator value.
		/// @return Numeric representation of data bits.
		/// Implementation should map CharacterSize values (e.g., CS8) to their
		/// corresponding integers (e.g., 8) for easier configuration handling.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual uint32_t dataBitsToUint(const CharacterSize data) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts numeric uint32_t to CharacterSize enum.
		/// @param data Numeric value.
		/// @return Scoped enumerator for data bits.
		/// Implementation should map common data bit integers (e.g., 5, 6, 7, 8)
		/// to their corresponding CharacterSize enums.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual CharacterSize uintToDataBits(const uint32_t data) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts Parity enum to numeric uint32_t.
		/// @param parity Scoped enumerator value.
		/// @return Numeric representation of parity.
		/// Implementation should map Parity values (e.g., None, Odd, Even)
		/// to their corresponding integers.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual uint32_t parityToUint(const Parity parity) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts numeric uint32_t to Parity enum.
		/// @param parity Numeric value.
		/// @return Scoped enumerator for parity.
		/// Implementation should map common parity integers (e.g., 0 for None,
		/// 1 for Odd, 2 for Even) to their corresponding Parity enums.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual Parity uintToParity(const uint32_t parity) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts StopBits enum to numeric uint32_t.
		/// @param stop Scoped enumerator value.
		/// @return Numeric representation of stop bits.
		/// Implementation should map StopBits values (e.g., One, Two) to
		/// their corresponding integers (e.g., 1, 2).
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual uint32_t stopBitsToUint(const StopBits stop) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts numeric uint32_t to StopBits enum.
		/// @param stop Numeric value.
		/// @return Scoped enumerator for stop bits.
		/// Implementation should map common stop bit integers (e.g., 1, 2)
		/// to their corresponding StopBits enums.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual StopBits uintToStopBits(const uint32_t stop) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts FlowControl enum to numeric uint32_t.
		/// @param flow Scoped enumerator value.
		/// @return Numeric representation of flow control.
		/// Implementation should map FlowControl values (e.g., None, Software,
		/// Hardware) to their corresponding integers.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual uint32_t flowControlToUint(const FlowControl flow) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts numeric uint32_t to FlowControl enum.
		/// @param flow Numeric value.
		/// @return Scoped enumerator for flow control.
		/// Implementation should map common flow control integers (e.g., 0 for
		/// None, 1 for Software, 2 for Hardware) to their corresponding
		/// FlowControl enums for easier configuration handling.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual FlowControl uintToFlowControl(const uint32_t flow) = 0;

		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////
    };
}
