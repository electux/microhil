/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * config.h
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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

#include "iconfig.h"
#include "../model/model_serial.h"
#include "../model/model_log.h"

namespace Electux::App::Model { class ModelSerial; }
namespace Electux::App::Model { class ModelLog; }

namespace Electux::App::Config
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Config class is implementation for configuration mechanism
    class Config : public IConfig
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Config constructor
        explicit Config();

        //////////////////////////////////////////////////////////////////////
        /// @brief Loads configuration
        /// @return status true for success load configuration else false
        bool load() final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Stores configuration
        /// @return status true for success store configuration else false
        bool store() final;

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Configuration parameters and properties
        ///   m_file_name - file name path for load/store configuration
        ///   m_serial_config - serial port configuration
        ///   m_log_config - log configuration
        std::string m_file_name;
        Model::ModelSerial m_serial_config;
        Model::ModelLog m_log_config;
    };
};

