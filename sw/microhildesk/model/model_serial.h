/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model_serial.h
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

#include "model.h"

namespace Electux::App::Model
{
    class ModelSerial : public Model
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief ModelSerial constructor
        inline ModelSerial() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Enum for serial configuration keys
        enum class ModelSerialKey
        {
            Device,
            Baud,
            Data,
            Parity,
            Stop,
            Flow
        };

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets all model entries
        /// @return Map of all model entries {key: data}
        Entities getAllEntries() const final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Converts Key enum to 
        /// @param key Represents ModelSerialKey enum value
        /// @return string representation of ModelSerialKey enum
        std::string toString(const ModelSerialKey &key) const;

        //////////////////////////////////////////////////////////////////////
        /// @brief Validates if key is valid serial configuration key
        /// @param key Represents string key to be validated
        /// @return status true if key is valid else false
        bool validateKey(const std::string &key) const;
    };
};

