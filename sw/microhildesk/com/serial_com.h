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
    ///////////////////////////////////////////////////////////////////////////
    /// @brief SerialCom class is implementation of serial communication
    class SerialCom : public ICom
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief SerialCom methods
        ///   SerialCom constructor
        ///   SerialCom destructor
        inline SerialCom() noexcept = default;
        ~SerialCom() noexcept;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Opens the serial communication channel
        void open() final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Closes the serial communication channel
        void close() final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Setup the serial port parameters
        /// @param params represents parameters for the serial port
        void setup(const SerialParams &params) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Read from serial communication channel
        /// @param data represents data to be placed to after reading
        /// @param len represents length of data to read before returning
        void read(std::vector<uint8_t> &data, size_t len) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Writes data to the serial communication channel
        /// @param data represents data to be written to the serial port
        void write(const std::vector<uint8_t> &data) final;

    protected:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from scopped enumerator to uint32_t
        /// @param baud represents scoped enumerator value
        /// @return uint32_t format of baud-rate
        uint32_t baudToUint(const BaudRate baud) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts baud-rate from uint32_t to scopped enumerator
        /// @param baud represents uint32_t value
        /// @return scoped enumerator format of baud-rate
        BaudRate uintToBaud(const uint32_t baud) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from scopped enumerator to uint32_t
        /// @param data represents scoped enumerator value
        /// @return uint32_t format of data-bits
        uint32_t dataBitsToUint(const CharacterSize data) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts data-bits from uint32_t to scopped enumerator
        /// @param data represents uint32_t format
        /// @return scoped enumerator format of data-bits
        CharacterSize uintToDataBits(const uint32_t data) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from scopped enumerator to uint32_t
        /// @param parity represents scoped enumerator value
        /// @return uint32_t format of parity
        uint32_t parityToUint(const Parity parity) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts parity from uint32_t to scopped enumerator
        /// @param parity represents uint32_t format
        /// @return scoped enumerator format of parity
        Parity uintToParity(const uint32_t parity) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from scopped enumerator to uint32_t
        /// @param stop represents scoped enumerator value
        /// @return uint32_t format of stop-bits
        uint32_t stopBitsToUint(const StopBits stop) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts stop-bits from uint32_t to scopped enumerator
        /// @param stop represents uint32_t format
        /// @return scoped enumerator format of stop-bits
        StopBits uintToStopBits(const uint32_t stop) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from scopped enumerator to uint32_t
        /// @param flow represents scoped enumerator value
        /// @return uint32_t format of flow-control
        uint32_t flowControlToUint(const FlowControl flow) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Converts flow-control from uint32_t to scopped enumerator
        /// @param flow represents uint32_t format
        /// @return scoped enumerator format of flow-control
        FlowControl uintToFlowControl(const uint32_t flow) final;

    private:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Serial port instance
        SerialPort m_serialPort{};

        ///////////////////////////////////////////////////////////////////////
        /// @brief Serial port device file path
        std::string m_device{};
    };
};

