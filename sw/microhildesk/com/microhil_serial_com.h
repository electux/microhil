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

#include "microhil_icom.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHSerialCom class is implementation of serial communication
class MHSerialCom : public IMHCom
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILCom constructor
    explicit MHSerialCom();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Opens the serial communication channel
    void open() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Closes the serial communication channel
    void close() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts baud-rate from scopped enumerator to unsigned int
    /// @param baudRate represents scoped enumerator value
    /// @return unsigned integer format of baud-rate
    unsigned int baudRateToUInt(const BaudRate baudRate) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts baud-rate from unsigned int to scopped enumerator
    /// @param baudRate represents unsigned integer value
    /// @return scoped enumerator format of baud-rate
    BaudRate uintToBaudRate(const unsigned int baudRate) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts data-bits from scopped enumerator to unsigned int
    /// @param dataBits represents scoped enumerator value
    /// @return unsigned integer format of data-bits
    unsigned int dataBitsToUInt(const CharacterSize dataBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts data-bits from unsigned int to scopped enumerator
    /// @param dataBits represents unsigned integer format
    /// @return scoped enumerator format of data-bits
    CharacterSize uintToDataBits(const unsigned int dataBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity from scopped enumerator to unsigned int
    /// @param parity represents scoped enumerator value
    /// @return unsigned integer format of parity
    unsigned int parityToUInt(const Parity parity) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts parity from unsigned int to scopped enumerator
    /// @param parity represents unsigned integer format
    /// @return scoped enumerator format of parity
    Parity uintToParity(const unsigned int parity) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits from scopped enumerator to unsigned int
    /// @param stopBits represents scoped enumerator value
    /// @return unsigned integer format of stop-bits
    unsigned int stopBitsToUInt(const StopBits stopBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts stop-bits from unsigned int to scopped enumerator
    /// @param stopBits represents unsigned integer format
    /// @return scoped enumerator format of stop-bits
    StopBits uintToStopBits(const unsigned int stopBits) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device represents file path for the serial port
    /// @param params represents parameters for the serial port
    void setup(const MHString &device, const MHVecUInt &params) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup the serial port parameters
    /// @param device represents file path for the serial port
    /// @param params represents parameters for the serial port
    void setup(const MHString &device, const MHSerialParams &params) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Read from serial communication channel
    /// @param data represents data to be placed to after reading
    /// @param len represents length of data to read before returning
    /// @param timeout represents timeout period in miliseconds
    void read(MHVecByte &data, size_t len, size_t timeout) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Writes data to the serial communication channel
    /// @param data represents data to be written to the serial port
    void write(const MHVecByte &data) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    MHUPtr<SerialPort> m_serialPort{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port device file path
    MHString m_device{};
};
