/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_icom.h
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
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

#include "../utils/microhil_types.h"
#include <libserial/SerialPort.h>

using LibSerial::BaudRate;
using LibSerial::CharacterSize;
using LibSerial::Parity;
using LibSerial::SerialPort;
using LibSerial::StopBits;

////////////////////////////////////////////////////////////////////////////
/// @brief Declaration of serial parameters structure
using MHSerialParams = struct
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief The serial port baud-rate parameter
    BaudRate baudRate;

    ////////////////////////////////////////////////////////////////////////
    /// @brief The serial port data-bits parameter
    CharacterSize dataBits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief The serial port parity parameter
    Parity parity;

    ////////////////////////////////////////////////////////////////////////
    /// @brief The serial port stop-bits parameter
    StopBits stopBits;
};

////////////////////////////////////////////////////////////////////////////
/// @brief IMHCom class is interface set for serial communication
class IMHCom
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHCom destructor
    inline virtual ~IMHCom() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Opens communication channel
    virtual void open() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Closes communication channel
    virtual void close() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device represents file path for the serial port
    /// @param params represents parameters for the serial port
    virtual void setup(const UString &device, const VecUInt &params) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device file path for the serial port
    /// @param params for the serial port
    virtual void setup(const UString &device, const MHSerialParams &params) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Reads from the communication channel
    /// @param data represents buffer to be placed to after reading channel
    /// @param len represents length of data to read before returning
    /// @param timeout represents timeout period in miliseconds
    virtual void read(VecByte &data, size_t len, size_t timeout) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Writes to the communication channel
    /// @param data represents data to be written to channel
    virtual void write(const VecByte &data) = 0;

protected:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts baud-rate from scopped enumerator to unsigned int
    /// @param baudRate represents scoped enumerator value
    /// @return unsigned integer format of baud-rate
    virtual unsigned int baudRateToUInt(const BaudRate baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts baud-rate from unsigned int to scopped enumerator
    /// @param baudRate represents unsigned integer value
    /// @return scoped enumerator format of baud-rate
    virtual BaudRate uintToBaudRate(const unsigned int baudRate) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts data-bits from scopped enumerator to unsigned int
    /// @param dataBits represents scoped enumerator value
    /// @return unsigned integer format of data-bits
    virtual unsigned int dataBitsToUInt(const CharacterSize dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts data-bits from unsigned int to scopped enumerator
    /// @param dataBits represents unsigned integer format
    /// @return scoped enumerator format of data-bits
    virtual CharacterSize uintToDataBits(const unsigned int dataBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity from scopped enumerator to unsigned int
    /// @param parity represents scoped enumerator value
    /// @return unsigned integer format of parity
    virtual unsigned int parityToUInt(const Parity parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity from unsigned int to scopped enumerator
    /// @param parity represents unsigned integer format
    /// @return scoped enumerator format of parity
    virtual Parity uintToParity(const unsigned int parity) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits from scopped enumerator to unsigned int
    /// @param stopBits represents scoped enumerator value
    /// @return unsigned integer format of stop-bits
    virtual unsigned int stopBitsToUInt(const StopBits stopBits) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits from unsigned int to scopped enumerator
    /// @param stopBits represents unsigned integer format
    /// @return scoped enumerator format of stop-bits
    virtual StopBits uintToStopBits(const unsigned int stopBits) = 0;
};
