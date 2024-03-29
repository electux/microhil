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

#include "../com/microhil_serial_com.h"
#include "../config/microhil_config.h"
#include "../log/microhil_log.h"
#include "../model/microhil_model.h"
#include "../view/microhil_view.h"
#include "microhil_icontroller.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHController class is implementation of controller
class MHController : public IMHController
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHController constructor
    /// @param model represents model instance
    /// @param view represents view instance
    explicit MHController(SPtr<IMHModel> model, SPtr<IMHView> view);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHController destructor
    inline ~MHController() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enables controller (enable/disable communication)
    /// @param switchController represents requested enable value
    void setEnabled(bool switchController) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks is controller enabled (is serial communication enabled)
    /// @return status true for enabled else false
    bool isEnabled() const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps views and backend (signals and slots)
    void mapping() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings changes
    /// @param path represents absolute path of log file
    /// @param level represents level for logging messages
    void onLogSettingsChanged(UString &path, int level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log settings loaded
    /// @param path represents absolute path of log file
    /// @param logLevel represents level for logging messages
    void onLogSettingsLoaded(UString &path, int level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev represents file path for serial device
    /// @param params represents set of serial parameters
    void onSerialSettingsChanged(UString &dev, VecUInt &params) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param dev represents file path for serial device
    /// @param params represents set of serial parameters
    void onSerialSettingsLoaded(UString &dev, VecUInt &params) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial port changes
    /// @param state true for enable port, else false
    void onSerialControlChanged(bool state) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable/Disable state of controller
    bool m_enabled{false};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Model instance
    SPtr<IMHModel> m_model{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief View instance
    SPtr<IMHView> m_view{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    SPtr<IMHConfig> m_config{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log instance
    SPtr<IMHLog> m_log{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    SPtr<IMHCom> m_serial{nullptr};
};
