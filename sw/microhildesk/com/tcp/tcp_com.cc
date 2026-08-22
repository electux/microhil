////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com.cc
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

#include <arpa/inet.h>
#include <com/tcp/tcp_com.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Electux::App::Com;

TcpCom::TcpCom() : m_ip("127.0.0.1"), m_port(5000), m_socketFd(-1) {
    std::cout << "TcpCom constructor called." << std::endl;
}

TcpCom::~TcpCom() noexcept {
    close();
    std::cout << "TcpCom destructor called." << std::endl;
}

bool TcpCom::open() {
    if (isOpen()) {
        return true;
    }

    m_socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd < 0) {
        std::cerr << "TcpCom open error: Failed to create socket." << std::endl;
        return false;
    }

    struct sockaddr_in serv_addr;
    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);

    if (::inet_pton(AF_INET, m_ip.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr
            << "TcpCom open error: Invalid address or Address not supported."
            << std::endl;
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    if (::connect(
            m_socketFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)
        ) < 0) {
        std::cerr << "TcpCom open error: Connection Failed." << std::endl;
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    std::cout << "TcpCom connected successfully to " << m_ip << ":" << m_port
              << std::endl;
    return true;
}

bool TcpCom::close() {
    if (isOpen()) {
        ::close(m_socketFd);
        m_socketFd = -1;
        std::cout << "TcpCom connection closed." << std::endl;
        return true;
    }
    return false;
}

bool TcpCom::isOpen() const { return m_socketFd != -1; }

void TcpCom::read(std::vector<uint8_t> &data, size_t len) {
    if (!isOpen()) {
        return;
    }

    data.resize(len);
    size_t totalRead = 0;
    while (totalRead < len) {
        ssize_t bytesRead =
            ::recv(m_socketFd, data.data() + totalRead, len - totalRead, 0);
        if (bytesRead <= 0) {
            std::cerr << "TcpCom read: Connection lost or read error."
                      << std::endl;
            close();
            break;
        }
        totalRead += static_cast<size_t>(bytesRead);
    }
}

void TcpCom::write(const std::vector<uint8_t> &data) {
    if (!isOpen()) {
        std::cerr << "TcpCom write error: Connection is not open." << std::endl;
        return;
    }

    size_t totalSent = 0;
    while (totalSent < data.size()) {
        ssize_t bytesSent = ::send(
            m_socketFd, data.data() + totalSent, data.size() - totalSent, 0
        );
        if (bytesSent <= 0) {
            std::cerr << "TcpCom write: Connection lost or write error."
                      << std::endl;
            close();
            break;
        }
        totalSent += static_cast<size_t>(bytesSent);
    }
}

void TcpCom::setIpAddress(const std::string &ip) { m_ip = ip; }

void TcpCom::setPort(uint16_t port) { m_port = port; }
