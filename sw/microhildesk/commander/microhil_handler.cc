/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_handler.h
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
#include "microhil_handler.h"

void Handler::registerCommand(const std::string &key, MHCommand op)
{
    m_commandTable[key] = op;
}

void Handler::executeCommand(const std::string &key)
{
    auto command = m_commandTable.find(key);

    if (command != m_commandTable.end())
    {
        command->second(key);
    }
    else
    {
        std::cout << "Unknown operation\n";
        // TODO
        // Emit signal for error handler
    }
}

std::vector<std::string> Handler::getSupportedCommands() const
{
    std::vector<std::string> keys;

    keys.reserve(m_commandTable.size());

    for (auto pair : m_commandTable)
    {
        keys.push_back(pair.first);
    }

    return keys;
}
