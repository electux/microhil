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

void MicroHILController::mapping()
{
    ////////////////////////////////////////////////////////////////////////
    /// Map log settings signal from configuration with controller slot
    m_config->LogConfigLoaded().connect(
        sigc::mem_fun(*this, &MicroHILController::onLogSettingsLoaded)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map serial settings signal from configuration with controller slot
    m_config->SerialConfigLoaded().connect(
        sigc::mem_fun(*this, &MicroHILController::onSerialSettingsLoaded)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map log view signal with controller slot
    m_view->getLogSettings()->logSetupChanged().connect(
        sigc::mem_fun(*this, &MicroHILController::onLogSettingsChanged)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map serial view signal with controller slot
    m_view->getSerialSettings()->serialSetupChanged().connect(
        sigc::mem_fun(*this, &MicroHILController::onSerialSettingsChanged)
    );
}
