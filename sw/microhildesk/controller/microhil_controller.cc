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

MicroHILController::MicroHILController(
    std::shared_ptr<MicroHILModel> model, std::shared_ptr<MicroHILView> view
)
{
    ////////////////////////////////////////////////////////////////////////
    // Prepare and setup configuration, log and serial
    m_config = make_unique<MicroHILConfig>();
    m_log = make_unique<MicroHILLog>();
    m_serial = make_unique<MicroHILSerialCom>();

    ////////////////////////////////////////////////////////////////////////
    // Checking existance of configuration
    if(!m_config->isPreValid())
    {
        // TODO
        // Emit signal for error handler
    }

    ////////////////////////////////////////////////////////////////////////
    // Loading configuration from file
    if(!m_config->load())
    {
        // TODO
        // Emit signal for error handler
    }

    ////////////////////////////////////////////////////////////////////////
    // Setup log file destination from configuration
    m_log->setFilePath(m_config->getLogFile());

    if(!m_log->open())
    {
        // TODO
        // Emit signal for error handler
    }
}

void MicroHILController::setEnabled(bool switchController)
{
    m_enabled = switchController;
}

bool MicroHILController::isEnabled() const
{
    return m_enabled;
}
