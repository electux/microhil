/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_controller.cc
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

MHController::MHController(SPtr<IMHModel> model, SPtr<IMHView> view)
    : m_model{model}
    , m_view{view}
    , m_config{makeSPtr<MHConfig>()}
    , m_log{makeSPtr<MHLog>()}
    , m_serial{makeSPtr<MHSerialCom>()}
{
    ////////////////////////////////////////////////////////////////////////
    /// Maps views and backend (signals and slots)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Checks existance of configuration
    if (!m_config->isPreValid())
    {
        // TODO
        // Emit signal for error handler

        // TODO
        // logging
        return;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Loads configuration from file
    if (!m_config->load())
    {
        // TODO
        // Emit signal for error handler

        // TODO
        // logging
        return;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Sets log file destination from configuration
    m_log->setFilePath(m_config->getLogPath());

    ////////////////////////////////////////////////////////////////////////
    /// Sets log level from configuration
    m_log->setLogLevel(m_config->getLogLevel());

    if (!m_log->open())
    {
        // TODO
        // Emit signal for error handler

        // TODO
        // logging
        return;
    }
}

void MHController::setEnabled(bool switchController)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets controller state (enabled - true, or disabled - false)
    m_enabled = switchController;
}

bool MHController::isEnabled() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Checks is controller enabled
    return m_enabled;
}
