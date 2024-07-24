/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com.h
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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

#include "icom.h"

namespace Electux::App::Com
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief SerialCom class is implementation of serial communication
    class SerialCom : public ICom
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief MicroHILCom constructor
        explicit SerialCom();

        //////////////////////////////////////////////////////////////////////
        /// @brief SerialCom destructor
        inline ~SerialCom() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Opens the serial communication channel
        void open() final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Closes the serial communication channel
        void close() final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Setup the serial port parameters
        /// @param params represents parameters for the serial port
        void setup(const SerialParams &params) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Read from serial communication channel
        /// @param data represents data to be placed to after reading
        /// @param len represents length of data to read before returning
        void read(std::vector<uint8_t> &data, size_t len) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Writes data to the serial communication channel
        /// @param data represents data to be written to the serial port
        void write(const std::vector<uint8_t> &data) final;

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from scopped enumerator to unsigned int
        /// @param baud represents scoped enumerator value
        /// @return unsigned integer format of baud-rate
        unsigned int baud_to_uint(const BaudRate baud) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from unsigned int to scopped enumerator
        /// @param baud represents unsigned integer value
        /// @return scoped enumerator format of baud-rate
        BaudRate uint_to_baud(const unsigned int baud) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from scopped enumerator to unsigned int
        /// @param data represents scoped enumerator value
        /// @return unsigned integer format of data-bits
        unsigned int data_bits_to_uint(const CharacterSize data) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from unsigned int to scopped enumerator
        /// @param data represents unsigned integer format
        /// @return scoped enumerator format of data-bits
        CharacterSize uint_to_data_bits(const unsigned int data) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from scopped enumerator to unsigned int
        /// @param parity represents scoped enumerator value
        /// @return unsigned integer format of parity
        unsigned int parity_to_uint(const Parity parity) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from unsigned int to scopped enumerator
        /// @param parity represents unsigned integer format
        /// @return scoped enumerator format of parity
        Parity uint_to_parity(const unsigned int parity) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from scopped enumerator to unsigned int
        /// @param stop represents scoped enumerator value
        /// @return unsigned integer format of stop-bits
        unsigned int stop_bits_to_uint(const StopBits stop) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from unsigned int to scopped enumerator
        /// @param stop represents unsigned integer format
        /// @return scoped enumerator format of stop-bits
        StopBits uint_to_stop_bits(const unsigned int stop) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Serial port instance
        SerialPort m_serialPort;

        //////////////////////////////////////////////////////////////////////
        /// @brief Serial port device file path
        std::string m_device{};
    };
};

