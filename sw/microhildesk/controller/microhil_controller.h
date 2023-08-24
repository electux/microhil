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

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILController class declaration and definition 
class MicroHILController: public AbMicroHILController
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILController constructor
    /// @param model instance
    /// @param view instance
    MicroHILController(
        std::shared_ptr<MicroHILModel> model,
        std::shared_ptr<MicroHILView> view
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILController destructor
    ~MicroHILController() = default;

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
    /// @param logPath is absolute path of log file
    /// @param logLevel is level for logging messages
    void onLogSettingsChanged(Glib::ustring logPath, int logLevel);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing serial settings changes
    /// @param device file path
    /// @param baudRate for serial port
    /// @param dataBits for serial port
    /// @param parity for serial port
    /// @param stopBits for serial port
    void onSerialSettingsChanged(
        Glib::ustring device, unsigned int baudRate, unsigned int dataBits,
        unsigned int parity, unsigned int stopBits
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable/Disable state of controller
    bool m_enabled{false};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Model instance
    std::shared_ptr<MicroHILModel> m_model{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief View instance
    std::shared_ptr<MicroHILView> m_view{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Configuration instance
    std::unique_ptr<MicroHILConfig> m_config{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log instance 
    std::unique_ptr<MicroHILLog> m_log{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial port instance
    std::unique_ptr<MicroHILSerialCom> m_serial{nullptr};
};
