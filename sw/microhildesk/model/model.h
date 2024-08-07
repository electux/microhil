/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model.h
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

#include "imodel.h"

namespace Electux::App::Model
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Model definition
    class Model : public IModel
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Model constructor
        inline Model() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Adds entity to model {'key': 'data'}
        /// @param key Represents model enity key to be added
        /// @param data Represents model entity data to be added
        bool add(const std::string &key, const std::string &data) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets entity by key
        /// @param key Represents model enity key
        /// @return Entity selected by key
        std::string &get_entity(const std::string &key) final;

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets model entities
        /// @return Model entities in format map of strings
        const Entities &get() const final;

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Model entities in format map of strings {key: data}
        Entities m_entities;
    };
};

