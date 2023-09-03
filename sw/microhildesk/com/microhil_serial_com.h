/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_serial_com.h
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

#include <libserial/SerialPort.h>
#include "microhil_com_abstract.h"

using LibSerial::SerialPort;
using LibSerial::BaudRate;
using LibSerial::CharacterSize;
using LibSerial::Parity;
using LibSerial::StopBits;

////////////////////////////////////////////////////////////////////////////
/// @brief Declaration of serial parameters structure
using MHSerialParams = struct 
{
    BaudRate baudRate;
    CharacterSize dataBits;
    Parity parity;
    StopBits stopBits;
};

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILSerialCom class declaration and definition
class MicroHILSerialCom: public AbMicroHILCom
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILCom constructor
    MicroHILSerialCom();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILCom destructor
    ~MicroHILSerialCom();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Open the serial communication channel
    void open() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Close the serial communication channel
    void close() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert baud-rate from scopped enumerator to unsigned int 
    /// @param baudRate in scoped enumerator value
    /// @return unsigned integer format of baud-rate
    unsigned int baudRateToUInt(const BaudRate baudRate);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert baud-rate from unsigned int to scopped enumerator 
    /// @param baudRate in unsigned integer value
    /// @return scoped enumerator format of baud-rate
    BaudRate uintToBaudRate(const unsigned int);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert data-bits from scopped enumerator to unsigned int 
    /// @param dataBits in scoped enumerator value
    /// @return unsigned integer format of data-bits
    unsigned int dataBitsToUInt(const CharacterSize dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert data-bits from unsigned int to scopped enumerator 
    /// @param dataBits in unsigned integer format
    /// @return scoped enumerator format of data-bits
    CharacterSize uintToDataBits(const unsigned int dataBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert parity from scopped enumerator to unsigned int 
    /// @param parity in scoped enumerator value
    /// @return unsigned integer format of parity
    unsigned int parityToUInt(const Parity parity);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert parity from unsigned int to scopped enumerator 
    /// @param parity in unsigned integer format
    /// @return scoped enumerator format of parity
    Parity uintToParity(const unsigned int parity);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert stop-bits from scopped enumerator to unsigned int 
    /// @param stopBits in scoped enumerator value
    /// @return unsigned integer format of stop-bits
    unsigned int stopBitsToUInt(const StopBits stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert stop-bits from unsigned int to scopped enumerator 
    /// @param stopBits in unsigned integer format
    /// @return scoped enumerator format of stop-bits
    StopBits uintToStopBits(const unsigned int stopBits);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device file path for serial port
    /// @param params for serial port
    void setup(MHString device, MHVecUInt params);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device file path for the serial port
    /// @param params for the serial port
    void setup(MHString device, MHSerialParams params);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Read from serial communication channel
    /// @param data buffer to be placed to after reading the serial port
    /// @param len length of data to read before returning
    /// @param timeout timeout period in miliseconds
    void read(MHVecByte& data, size_t len, size_t timeout) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Write data to the serial communication channel
    /// @param data to be written to the serial port
    void write(MHVecByte& data) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    MHUPtr<SerialPort> m_serialPort{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port device file path
    MHString m_device{};
};
