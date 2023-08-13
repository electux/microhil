/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_controller.h
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
#pragma once

#include <memory>
#include "../config/microhil_config.h"
#include "../log/microhil_log.h"
#include "../com/microhil_serial_com.h"
#include "../model/microhil_model.h"
#include "../view/microhil_view.h"
#include "microhil_controller_abstract.h"

class MicroHILController: public AbMicroHILController
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILController constructor
    MicroHILController(MicroHILModel *model, MicroHILView *view);

    ////////////////////////////////////////////////////////////////////////
    // MicroHILController destructor
    ~MicroHILController() = default;

    ////////////////////////////////////////////////////////////////////////
    // Enable controller (enable/disable communication)
    void setEnabled(bool switchController) final;

    ////////////////////////////////////////////////////////////////////////
    // Check is controller enabled (is serial communication enabled)
    bool isEnabled() const final;

private:
    bool m_enabled {};

    std::unique_ptr<MicroHILConfig> m_config{nullptr};
    std::unique_ptr<MicroHILLog> m_log{nullptr};
    std::unique_ptr<MicroHILSerialCom> m_serial{nullptr};
};
