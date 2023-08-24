/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_log_slots.cc
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
#include <filesystem>
#include "microhil_view_log.h"

void MicroHILViewLog::onLogFilePathChanged()
{
    auto logPath = m_device->get_text();

    auto logPathExists = std::filesystem::exists(std::string(logPath));

    if(logPathExists)
    {
        // TODO Dialog message box with confirmation
    }
}

void MicroHILViewLog::onLogLevelChanged()
{
    // TODO
}

void MicroHILViewLog::onCancelLogTriggered()
{
    this->hide();
}

void MicroHILViewLog::onOkLogTriggered()
{
    auto logPath = m_device->get_text();
    auto logLevel = m_level->get_active_row_number();

    ////////////////////////////////////////////////////////////////////////
    /// Emit new log settings 
    m_logSetup.emit(logPath, logLevel);

    this->hide();
}
