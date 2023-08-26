/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_controller_slots.cc
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
#include "microhil_controller.h"

void MicroHILController::onLogSettingsChanged(
    Glib::ustring logPath, int logLevel
)
{
    ////////////////////////////////////////////////////////////////////////
    /// Update log configuration
    m_config->setLogPath(logPath);
    m_config->setLogLevel(logLevel);

    if (!m_config->store())
    {
        // TODO error handler
    }

    ////////////////////////////////////////////////////////////////////////
    /// Update log handler
    m_log->close();
    m_log->setFilePath(logPath);
    m_log->setLogLevel(logLevel);
    m_log->open();
}

void MicroHILController::onSerialSettingsChanged(
    Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
    unsigned int parity, unsigned int stopBits
)
{
    ////////////////////////////////////////////////////////////////////////
    /// Update serial configuration
    m_config->setDevice(device);
    m_config->setBaudRate(baudRate);
    m_config->setDataBits(dataBits);
    m_config->setParity(parity);
    m_config->setStopBits(stopBits);

    if (!m_config->store())
    {
        // TODO error handler
    }

    ////////////////////////////////////////////////////////////////////////
    /// Update serial handler
    // m_serial->close();
    // m_serial->setup(device, baudRate, dataBits, parity, stopBits);
    // TODO dialog message to open port?
    // m_serial->open();
}
