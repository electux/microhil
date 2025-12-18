/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * imodel.h
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

#include <map>
#include <string>

namespace Electux::App::Model
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Model entities in map format {'key': 'data'}
    using Entities = std::map<std::string, std::string>;

    //////////////////////////////////////////////////////////////////////////
    /// @brief IModel declaration
    class IModel
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief IModel destructor
        virtual ~IModel() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Adds entity to model {'key': 'data'}
        /// @param key Represents model enity key to be added
        /// @param data Represents model entity data to be added
        /// @return True for success operation, otherwise false
        virtual bool add(const std::string &key, const std::string &data) = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets entity by key
        /// @param key Represents model enity key
        /// @return Entity selected by key
        virtual std::string &get_entity(const std::string &key) = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets model entities
        /// @return Model entities in format map of strings {key: data}
        virtual const Entities &get() const = 0;
    };
};

