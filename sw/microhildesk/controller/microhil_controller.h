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

#include "../config/microhil_config.h"
#include "../log/microhil_log.h"
#include "../com/microhil_serial_com.h"
#include "../model/microhil_model.h"
#include "../view/microhil_view.h"
#include "microhil_controller_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHController class declaration and definition
class MHController : public AbMHController
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHController constructor
    /// @param model instance
    /// @param view instance
    MHController(MHSPtr<MHModel> model, MHSPtr<MHView> view);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHController destructor
    ~MHController() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable controller (enable/disable communication)
    /// @param switchController request value
    void setEnabled(bool switchController) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check is controller enabled (is serial communication enabled)
    /// @return boolean status true for enabled else false
    bool isEnabled() const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Mapping views and backend (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings changes
    /// @param path is absolute path of log file
    /// @param level is level for logging messages
    void onLogSettingsChanged(MHString path, int level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings loaded
    /// @param path is absolute path of log file
    /// @param logLevel is level for logging messages
    void onLogSettingsLoaded(MHString path, int level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev file path for serial device
    /// @param params set of serial parameters
    void onSerialSettingsChanged(MHString dev, MHVecUInt params);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev file path for serial device
    /// @param params set of serial parameters
    void onSerialSettingsLoaded(MHString dev, MHVecUInt params);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable/Disable state of controller
    bool m_enabled{false};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Model instance
    MHSPtr<MHModel> m_model{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief View instance
    MHSPtr<MHView> m_view{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    MHUPtr<MHConfig> m_config{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log instance
    MHUPtr<MHLog> m_log{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    MHUPtr<MHSerialCom> m_serial{nullptr};
};
