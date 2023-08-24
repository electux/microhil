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

#include <memory>
#include <libserial/SerialPort.h>
#include <glibmm/ustring.h>
#include "microhil_com_abstract.h"

using LibSerial::SerialPort;
using LibSerial::BaudRate;
using LibSerial::CharacterSize;
using LibSerial::Parity;
using LibSerial::StopBits;

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
    /// @brief Setup serial port parameters
    /// @param device file path
    /// @param baudRate for serial port
    /// @param dataBits for serial port
    /// @param parity for serial port
    /// @param stopBits for serial port
    void setup(
        Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
        unsigned int parity, unsigned int stopBits
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief Read from serial communication channel
    /// @param data buffer to be placed to after reading the serial port
    /// @param len length of data to read before returning
    /// @param timeout timeout period in miliseconds
    void read(v_uint8& data, size_t len, size_t timeout) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Write data to the serial communication channel
    /// @param data to be written to the serial port
    void write(v_uint8& data) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    std::unique_ptr<SerialPort> m_serialPort{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port device file path
    Glib::ustring m_device{};
};
