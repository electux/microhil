////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// posix_serial_port.h
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <com/serial/driver/iserial_port.h>
#include <com/serial/driver/termios/iserial_termios_configurator.h>
#include <memory>
#include <string>
#include <vector>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class PosixSerialPort
    /// @brief Concrete POSIX Linux serial port implementation of ISerialPort.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class PosixSerialPort : public ISerialPort {
      public:
        explicit PosixSerialPort(
            std::unique_ptr<ISerialTermiosConfigurator> termiosConfigurator = nullptr
        );
        ~PosixSerialPort() override;

        PosixSerialPort(const PosixSerialPort &) = delete;
        PosixSerialPort &operator=(const PosixSerialPort &) = delete;

        void Open(const std::string &device) override;
        void Close() override;
        bool IsOpen() const override;

        void Read(std::vector<uint8_t> &data, size_t len) override;
        void Write(const std::vector<uint8_t> &data) override;

        void SetBaudRate(BaudRate baudRate) override;
        void SetCharacterSize(CharacterSize characterSize) override;
        void SetParity(Parity parity) override;
        void SetStopBits(StopBits stopBits) override;
        void SetFlowControl(FlowControl flowControl) override;

      private:
        void checkOpen() const;

        int m_fd{-1};
        std::string m_device{};
        std::unique_ptr<ISerialTermiosConfigurator> m_termiosConfigurator;
    };
} // namespace Electux::App::Com
