/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * icom.h
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <libserial/SerialPort.h>

namespace Electux::App::Com
{
	using SerialPort = LibSerial::SerialPort;
    using BaudRate = LibSerial::BaudRate;
    using CharacterSize = LibSerial::CharacterSize;
    using Parity = LibSerial::Parity;
    using StopBits = LibSerial::StopBits;
    using FlowControl = LibSerial::FlowControl;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Declaration of serial parameters structure
    struct SerialParams
    {
        ///////////////////////////////////////////////////////////////////////
        /// @brief Serial parameters
        ///   device - the serial port device file path
        ///   baud - the serial port baud-rate parameter
        ///   data - the serial port data-bits parameter
        ///   parity - the serial port parity parameter
        ///   stop - the serial port stop-bits parameter
        ///   flow - the serial port flow-control parameter
        std::string device;
        BaudRate baud;
        CharacterSize data;
        Parity parity;
        StopBits stop;
        FlowControl flow;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ICom class is interface for serial communication
    class ICom
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief ICom destructor
        inline virtual ~ICom() noexcept = default;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Opens communication channel
        virtual void open() = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Closes communication channel
        virtual void close() = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Setup the serial port parameters
        /// @param params for the serial port configuration
        virtual void setup(const SerialParams &params) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Reads from the communication channel
        /// @param data represents buffer to be placed to after reading channel
        /// @param len represents length of data to read before returning
        virtual void read(std::vector<uint8_t> &data, size_t len) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Writes to the communication channel
        /// @param data represents data to be written to channel
        virtual void write(const std::vector<uint8_t> &data) = 0;

    protected:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from scopped enumerator to uint32_t
        /// @param baud represents scoped enumerator value
        /// @return uint32_t format of baud-rate
        virtual uint32_t baudToUint(const BaudRate baud) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from uint32_t to scopped enumerator
        /// @param baud represents uint32_t value
        /// @return scoped enumerator format of baud-rate
        virtual BaudRate uintToBaud(const uint32_t baud) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from scopped enumerator to uint32_t
        /// @param data represents scoped enumerator value
        /// @return uint32_t format of data-bits
        virtual uint32_t dataBitsToUint(const CharacterSize data) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from uint32_t to scopped enumerator
        /// @param data represents uint32_t format
        /// @return scoped enumerator format of data-bits
        virtual CharacterSize uintToDataBits(const uint32_t data) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from scopped enumerator to uint32_t
        /// @param parity represents scoped enumerator value
        /// @return uint32_t format of parity
        virtual uint32_t parityToUint(const Parity parity) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from uint32_t to scopped enumerator
        /// @param parity represents uint32_t format
        /// @return scoped enumerator format of parity
        virtual Parity uintToParity(const uint32_t parity) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from scopped enumerator to uint32_t
        /// @param stop represents scoped enumerator value
        /// @return uint32_t format of stop-bits
        virtual uint32_t stopBitsToUint(const StopBits stop) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from uint32_t to scopped enumerator
        /// @param stop represents uint32_t format
        /// @return scoped enumerator format of stop-bits
        virtual StopBits uintToStopBits(const uint32_t stop) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from scopped enumerator to uint32_t
        /// @param flow represents scoped enumerator value
        /// @return uint32_t format of flow-control
        virtual uint32_t flowControlToUint(const FlowControl flow) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from uint32_t to scopped enumerator
        /// @param flow represents uint32_t format
        /// @return scoped enumerator format of flow-control
        virtual FlowControl uintToFlowControl(const uint32_t flow) = 0;
    };
};

