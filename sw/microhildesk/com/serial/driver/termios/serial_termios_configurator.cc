////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_termios_configurator.cc
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

#include <com/serial/driver/termios/serial_termios_configurator.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <termios.h>

using namespace Electux::App::Com;

namespace {
    constexpr const char *cTcgetattrErrorMsg{"tcgetattr failed: "};
    constexpr const char *cTcsetattrErrorMsg{"tcsetattr failed: "};
    constexpr const char *cInvalidBaudRateMsg{"Invalid baud rate."};
    constexpr const char *cInvalidCharacterSizeMsg{"Invalid character size."};
    constexpr const char *cInvalidParityMsg{"Invalid parity."};
    constexpr const char *cInvalidStopBitsMsg{"Invalid stop bits."};
    constexpr const char *cInvalidFlowControlMsg{"Invalid flow control."};
} // namespace

void SerialTermiosConfigurator::configureRawMode(int fd) {
    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }

    // Configure as raw serial port (binary mode)
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= ~OPOST;
    tty.c_iflag &=
        ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR |
          IGNCR | ICRNL);

    // Blocking read settings: return when at least 1 byte is available
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}

void SerialTermiosConfigurator::setBaudRate(int fd, BaudRate baudRate) {
    speed_t speed = B9600;
    switch (baudRate) {
    case BaudRate::BAUD_110:
        speed = B110;
        break;
    case BaudRate::BAUD_300:
        speed = B300;
        break;
    case BaudRate::BAUD_600:
        speed = B600;
        break;
    case BaudRate::BAUD_1200:
        speed = B1200;
        break;
    case BaudRate::BAUD_2400:
        speed = B2400;
        break;
    case BaudRate::BAUD_4800:
        speed = B4800;
        break;
    case BaudRate::BAUD_9600:
        speed = B9600;
        break;
    case BaudRate::BAUD_19200:
        speed = B19200;
        break;
    case BaudRate::BAUD_38400:
        speed = B38400;
        break;
    case BaudRate::BAUD_57600:
        speed = B57600;
        break;
    case BaudRate::BAUD_115200:
        speed = B115200;
        break;
    case BaudRate::BAUD_230400:
        speed = B230400;
        break;
    default:
        throw std::invalid_argument(cInvalidBaudRateMsg);
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}

void SerialTermiosConfigurator::setCharacterSize(
    int fd, CharacterSize characterSize
) {
    tcflag_t size = CS8;
    switch (characterSize) {
    case CharacterSize::CHAR_SIZE_5:
        size = CS5;
        break;
    case CharacterSize::CHAR_SIZE_6:
        size = CS6;
        break;
    case CharacterSize::CHAR_SIZE_7:
        size = CS7;
        break;
    case CharacterSize::CHAR_SIZE_8:
        size = CS8;
        break;
    default:
        throw std::invalid_argument(cInvalidCharacterSizeMsg);
    }

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= size;
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}

void SerialTermiosConfigurator::setParity(int fd, Parity parity) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }

    switch (parity) {
    case Parity::PARITY_NONE:
        tty.c_cflag &= ~PARENB;
        break;
    case Parity::PARITY_ODD:
        tty.c_cflag |= PARENB;
        tty.c_cflag |= PARODD;
        break;
    case Parity::PARITY_EVEN:
        tty.c_cflag |= PARENB;
        tty.c_cflag &= ~PARODD;
        break;
    default:
        throw std::invalid_argument(cInvalidParityMsg);
    }

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}

void SerialTermiosConfigurator::setStopBits(int fd, StopBits stopBits) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }

    switch (stopBits) {
    case StopBits::STOP_BITS_1:
        tty.c_cflag &= ~CSTOPB;
        break;
    case StopBits::STOP_BITS_2:
        tty.c_cflag |= CSTOPB;
        break;
    default:
        throw std::invalid_argument(cInvalidStopBitsMsg);
    }

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}

void SerialTermiosConfigurator::setFlowControl(
    int fd, FlowControl flowControl
) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcgetattrErrorMsg) + std::strerror(errno)
        );
    }

    switch (flowControl) {
    case FlowControl::FLOW_CONTROL_NONE:
        tty.c_cflag &= ~CRTSCTS;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    case FlowControl::FLOW_CONTROL_SOFTWARE:
        tty.c_cflag &= ~CRTSCTS;
        tty.c_iflag |= (IXON | IXOFF | IXANY);
        break;
    case FlowControl::FLOW_CONTROL_HARDWARE:
        tty.c_cflag |= CRTSCTS;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    default:
        throw std::invalid_argument(cInvalidFlowControlMsg);
    }

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            std::string(cTcsetattrErrorMsg) + std::strerror(errno)
        );
    }
}
