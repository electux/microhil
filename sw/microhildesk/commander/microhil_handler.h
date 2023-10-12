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
#pragma once

#include "microhil_ihandler.h"
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////
/// @brief Handler class is implementation of command handler
class Handler : public IHandler
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Handler constructor
    inline Handler() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Handler destructor
    inline ~Handler() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Prepares and register microHIL command
    /// @param key represents command key in string format
    /// @param op represents function wrapper for command
    void registerCommand(const std::string &key, MHCommand op) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Executes microHIL command
    /// @param key represents command key in string format
    void executeCommand(const std::string &key) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets supported commands
    /// @return command keys in string format
    std::vector<std::string> getSupportedCommands() const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map of command keys (string) and function wrappers
    std::unordered_map<std::string, MHCommand> m_commandTable;
};
