/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model.cc
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
#include <model/model.h>

using namespace Electux::App::Model;

bool Model::add(const std::string_view &key, const std::string_view &data)
{
    if (m_entities.find(key) != m_entities.end())
    {
        return false;
    }

    auto [it, inserted] = m_entities.emplace(std::string(key), std::string(data));
        
    return inserted;
}

const std::string &Model::getEntity(const std::string_view &key) const
{
    auto it = m_entities.find(key);
    if (it != m_entities.end())
    {
        return it->second;
    }

    static const std::string fallback{""};
    return fallback;
}

const Entities &Model::get() const
{
    return m_entities;
}

bool Model::update(const std::string_view &key, const std::string_view &data)
{
    auto it = m_entities.find(key);
    if (it != m_entities.end())
    {
        it->second = data;
        return true;
    }
    return false;
}

void Model::clear()
{
    m_entities.clear();
}
