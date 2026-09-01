////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_com.cc
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

#include <algorithm>
#include <chrono>
#include <com/ble/ble_com.h>
#include <com/ble/bluez/client/bluez_ble_client_factory.h>
#include <iostream>
#include <thread>

using namespace Electux::App::Com;

namespace {
    constexpr std::string_view cConstructorMsg{"BleCom constructor called."};
    constexpr std::string_view cDestructorMsg{"BleCom destructor called."};
    constexpr std::string_view cOpenSuccessMsg{"BleCom opened successfully."};
    constexpr std::string_view cCloseSuccessMsg{"BleCom closed successfully."};
    constexpr std::string_view cWriteError{
        "BleCom write error: Connection is not open."
    };
    constexpr std::chrono::milliseconds cReadTimeout{500};
} // namespace

BleCom::BleCom(bool verbose, std::unique_ptr<IBleClient> client)
    : m_address(""), m_serviceUuid(""), m_rxUuid(""), m_txUuid(""),
      m_verbose(verbose), m_client(std::move(client)) {
    if (m_verbose) {
        std::cout << cConstructorMsg << std::endl;
    }
}

BleCom::~BleCom() noexcept {
    close();
    if (m_verbose) {
        std::cout << cDestructorMsg << std::endl;
    }
}

bool BleCom::open() {
    if (m_isClosing) {
        return false;
    }

    std::unique_lock<std::mutex> lock(m_bufferMutex);
    if (m_client && m_client->isConnected()) {
        return true;
    }

    if (!m_client) {
        m_client = createBluezBleClient(
            m_address, m_serviceUuid, m_rxUuid, m_txUuid, m_verbose
        );
    }

    auto callback = [this](const std::vector<uint8_t> &data) {
        onNotificationReceived(data);
    };

    lock.unlock();

    if (m_isClosing) {
        return false;
    }

    if (m_client->connect(callback)) {
        if (m_verbose) {
            std::cout << cOpenSuccessMsg << std::endl;
        }
        return true;
    }

    return false;
}

bool BleCom::close() {
    m_isClosing = true;
    std::unique_lock<std::mutex> lock(m_bufferMutex);

    if (m_client) {
        m_client->abort();
        m_bufferCv.notify_all();
        lock.unlock();
        m_client->disconnect();

        if (m_verbose) {
            std::cout << cCloseSuccessMsg << std::endl;
        }

        return true;
    }

    m_bufferCv.notify_all();
    return false;
}

bool BleCom::isOpen() const {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    return m_client && m_client->isConnected();
}

void BleCom::read(std::vector<uint8_t> &data, size_t len) {
    data.clear();
    std::unique_lock<std::mutex> lock(m_bufferMutex);
    if (!m_client || !m_client->isConnected()) {
        return;
    }

    m_bufferCv.wait_for(lock, cReadTimeout, [this, len]() {
        return m_readBuffer.size() >= len || !m_client ||
               !m_client->isConnected();
    });

    if (m_readBuffer.empty()) {
        return;
    }

    size_t toCopy = std::min(len, m_readBuffer.size());
    data.assign(
        m_readBuffer.begin(),
        m_readBuffer.begin() +
            static_cast<std::vector<uint8_t>::difference_type>(toCopy)
    );
    m_readBuffer.erase(
        m_readBuffer.begin(),
        m_readBuffer.begin() +
            static_cast<std::vector<uint8_t>::difference_type>(toCopy)
    );
}

void BleCom::write(const std::vector<uint8_t> &data) {
    if (!isOpen()) {
        std::cerr << cWriteError << std::endl;
        return;
    }
    m_client->write(data);
}

void BleCom::setBleAddress(const std::string &address) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (m_address != address) {
        m_address = address;
        m_client.reset();
        m_isClosing = false;
    }
}

void BleCom::setServiceUuid(const std::string &uuid) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (m_serviceUuid != uuid) {
        m_serviceUuid = uuid;
        m_client.reset();
        m_isClosing = false;
    }
}

void BleCom::setRxUuid(const std::string &uuid) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (m_rxUuid != uuid) {
        m_rxUuid = uuid;
        m_client.reset();
        m_isClosing = false;
    }
}

void BleCom::setTxUuid(const std::string &uuid) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    if (m_txUuid != uuid) {
        m_txUuid = uuid;
        m_client.reset();
        m_isClosing = false;
    }
}

void BleCom::onNotificationReceived(const std::vector<uint8_t> &data) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    m_readBuffer.insert(m_readBuffer.end(), data.begin(), data.end());
    m_bufferCv.notify_all();
}
