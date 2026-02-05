/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_com.h
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

#include <com/icom.h>

namespace Electux::App::Com
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief SerialCom class is implementation of serial communication
    class SerialCom : public ICom
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief SerialCom methods
        ///   SerialCom constructor
        ///   SerialCom destructor
        inline SerialCom() noexcept = default;
        ~SerialCom() noexcept;

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
        unsigned int baudToUint(const BaudRate baud) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from unsigned int to scopped enumerator
        /// @param baud represents unsigned integer value
        /// @return scoped enumerator format of baud-rate
        BaudRate uintToBaud(const unsigned int baud) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from scopped enumerator to unsigned int
        /// @param data represents scoped enumerator value
        /// @return unsigned integer format of data-bits
        unsigned int dataBitsToUint(const CharacterSize data) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from unsigned int to scopped enumerator
        /// @param data represents unsigned integer format
        /// @return scoped enumerator format of data-bits
        CharacterSize uintToDataBits(const unsigned int data) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from scopped enumerator to unsigned int
        /// @param parity represents scoped enumerator value
        /// @return unsigned integer format of parity
        unsigned int parityToUint(const Parity parity) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from unsigned int to scopped enumerator
        /// @param parity represents unsigned integer format
        /// @return scoped enumerator format of parity
        Parity uintToParity(const unsigned int parity) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from scopped enumerator to unsigned int
        /// @param stop represents scoped enumerator value
        /// @return unsigned integer format of stop-bits
        unsigned int stopBitsToUint(const StopBits stop) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from unsigned int to scopped enumerator
        /// @param stop represents unsigned integer format
        /// @return scoped enumerator format of stop-bits
        StopBits uintToStopBits(const unsigned int stop) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from scopped enumerator to unsigned int
        /// @param flow represents scoped enumerator value
        /// @return unsigned integer format of flow-control
        unsigned int flowControlToUint(const FlowControl flow) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from unsigned int to scopped enumerator
        /// @param flow represents unsigned integer format
        /// @return scoped enumerator format of flow-control
        FlowControl uintToFlowControl(const unsigned int flow) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Serial port instance
        SerialPort m_serialPort{};

        //////////////////////////////////////////////////////////////////////
        /// @brief Serial port device file path
        std::string m_device{};
    };
};

