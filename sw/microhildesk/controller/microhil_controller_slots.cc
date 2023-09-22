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
#include <iostream>
#include "microhil_controller.h"

void MHController::onLogSettingsChanged(MHString &path, int level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Update the log configuration
    m_config->setLogPath(path);
    m_config->setLogLevel(level);

    if(!m_config->store())
    {
        // TODO error handler
        // TODO logging
    }

    ////////////////////////////////////////////////////////////////////////
    /// Update log handler
    m_log->close();
    m_log->setFilePath(path);
    m_log->setLogLevel(level);
    m_log->open();
    // TODO logging
}

void MHController::onLogSettingsLoaded(MHString &path, int level)
{
    m_view->getLogSettings()->logSettingsLoaded(path, level);
}

void MHController::onSerialSettingsChanged(MHString &dev, MHVecUInt &params)
{
    ////////////////////////////////////////////////////////////////////////
    /// Update the serial port configuration
    /// Note: Glib::KeyFile store only signed integers
    m_config->setDevice(dev);
    m_config->setBaudRate(static_cast<int>(params[0]));
    m_config->setDataBits(static_cast<int>(params[1]));
    m_config->setParity(static_cast<int>(params[2]));
    m_config->setStopBits(static_cast<int>(params[3]));

    if(!m_config->store())
    {
        // TODO error handler
        // TODO logging
    }

    ////////////////////////////////////////////////////////////////////////
    /// Update serial handler
    m_serial->close();
    // m_serial->setup(device, params);
    // TODO dialog message to open port?
    // m_serial->open();
    // TODO logging
}

void MHController::onSerialSettingsLoaded(MHString &dev, MHVecUInt &params)
{
    m_view->getSerialSettings()->serialSettingsLoaded(dev, params);
}
