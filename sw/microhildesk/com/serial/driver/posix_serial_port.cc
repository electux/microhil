////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// posix_serial_port.cc
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

#include <cerrno>
#include <com/serial/driver/posix_serial_port.h>
#include <com/serial/driver/termios/serial_termios_factory.h>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>

using namespace Electux::App::Com;

namespace {
    constexpr int cPollTimeoutMs{500};
    constexpr const char *cPortNotOpenMsg{"Port not open."};
    constexpr const char *cFailedToOpenMsg{"Failed to open device: "};
    constexpr const char *cDeviceDisconnectedFileMsg{
        "Device disconnected (file deleted)."
    };
    constexpr const char *cReadTimeoutMsg{"Timeout waiting for data."};
    constexpr const char *cPollFailedMsg{"Read error (poll failed): "};
    constexpr const char *cConnectionLostMsg{
        "Connection lost (device disconnected)."
    };
    constexpr const char *cReadErrorMsg{"Read error: "};
    constexpr const char *cConnectionLostEofMsg{"Connection lost (EOF)."};
    constexpr const char *cWriteErrorMsg{"Write error: "};
} // namespace

PosixSerialPort::PosixSerialPort(
    std::unique_ptr<ISerialTermiosConfigurator> termiosConfigurator
)
    : m_fd(-1), m_termiosConfigurator(
                    termiosConfigurator ? std::move(termiosConfigurator)
                                        : createSerialTermiosConfigurator()
                ) {}

PosixSerialPort::~PosixSerialPort() { Close(); }

void PosixSerialPort::checkOpen() const {
    if (m_fd < 0) {
        throw SerialNotOpen(cPortNotOpenMsg);
    }
}

void PosixSerialPort::Open(const std::string &device) {
    Close();
    m_device = device;
    m_fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_CLOEXEC);
    if (m_fd < 0) {
        throw std::runtime_error(
            std::string(cFailedToOpenMsg) + device + " (" +
            std::strerror(errno) + ")"
        );
    }

    try {
        m_termiosConfigurator->configureRawMode(m_fd);
    } catch (...) {
        close(m_fd);
        m_fd = -1;
        throw;
    }
}

void PosixSerialPort::Close() {
    if (m_fd >= 0) {
        close(m_fd);
        m_fd = -1;
    }
}

bool PosixSerialPort::IsOpen() const {
    if (m_fd < 0) {
        return false;
    }

    if (!m_device.empty() && !std::filesystem::exists(m_device)) {
        return false;
    }

    struct pollfd pfd;
    pfd.fd = m_fd;
    pfd.events = POLLIN | POLLERR | POLLHUP;
    pfd.revents = 0;
    int ret = poll(&pfd, 1, 0);

    if (ret > 0 && (pfd.revents & (POLLERR | POLLHUP | POLLNVAL))) {
        return false;
    }

    return true;
}

void PosixSerialPort::Read(std::vector<uint8_t> &data, size_t len) {
    checkOpen();
    data.clear();
    data.resize(len);
    size_t totalRead = 0;

    while (totalRead < len) {
        if (!m_device.empty() && !std::filesystem::exists(m_device)) {
            throw std::runtime_error(cDeviceDisconnectedFileMsg);
        }

        struct pollfd pfd;
        pfd.fd = m_fd;
        pfd.events = POLLIN | POLLERR | POLLHUP;
        pfd.revents = 0;

        int ret = poll(&pfd, 1, cPollTimeoutMs);
        if (ret == 0) {
            throw SerialReadTimeout(cReadTimeoutMsg);
        } else if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            throw std::runtime_error(
                std::string(cPollFailedMsg) + std::strerror(errno)
            );
        }

        if (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
            throw std::runtime_error(cConnectionLostMsg);
        }

        ssize_t n = read(m_fd, data.data() + totalRead, len - totalRead);
        if (n < 0) {
            if (errno == EAGAIN || errno == EINTR) {
                continue;
            }
            throw std::runtime_error(
                std::string(cReadErrorMsg) + std::strerror(errno)
            );
        } else if (n == 0) {
            throw std::runtime_error(cConnectionLostEofMsg);
        }
        totalRead += static_cast<size_t>(n);
        break;
    }

    data.resize(totalRead);
}

void PosixSerialPort::Write(const std::vector<uint8_t> &data) {
    checkOpen();
    size_t totalWritten = 0;

    while (totalWritten < data.size()) {
        ssize_t n =
            write(m_fd, data.data() + totalWritten, data.size() - totalWritten);

        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            throw std::runtime_error(
                std::string(cWriteErrorMsg) + std::strerror(errno)
            );
        }

        totalWritten += static_cast<size_t>(n);
    }
}

void PosixSerialPort::SetBaudRate(BaudRate baudRate) {
    checkOpen();
    m_termiosConfigurator->setBaudRate(m_fd, baudRate);
}

void PosixSerialPort::SetCharacterSize(CharacterSize characterSize) {
    checkOpen();
    m_termiosConfigurator->setCharacterSize(m_fd, characterSize);
}

void PosixSerialPort::SetParity(Parity parity) {
    checkOpen();
    m_termiosConfigurator->setParity(m_fd, parity);
}

void PosixSerialPort::SetStopBits(StopBits stopBits) {
    checkOpen();
    m_termiosConfigurator->setStopBits(m_fd, stopBits);
}

void PosixSerialPort::SetFlowControl(FlowControl flowControl) {
    checkOpen();
    m_termiosConfigurator->setFlowControl(m_fd, flowControl);
}
