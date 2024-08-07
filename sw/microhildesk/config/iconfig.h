/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * iconfig.h
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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

#include <string>

namespace Electux::App::Config
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief IConfig class is interface for configuration mechanism
    class IConfig
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief IConfig destructor
        inline virtual ~IConfig() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Loads configuration
        /// @return status true for success load configuration else false
        virtual bool load() = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief Stores configuration
        /// @return status true for success store configuration else false
        virtual bool store() = 0;
    };
};
