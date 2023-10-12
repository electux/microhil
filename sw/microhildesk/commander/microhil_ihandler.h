/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_ihandler.h
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

#include <functional>
#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////
/// @brief Function wrapper for microHIL commands
using MHCommand = std::function<void(const std::string &)>;

////////////////////////////////////////////////////////////////////////////
/// @brief IHandler class is interface set for command handler
class IHandler
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IHandler destructor
    inline virtual ~IHandler() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Prepares and register microHIL command
    /// @param key represents command key in string format
    /// @param op represents function wrapper for command
    virtual void registerCommand(const std::string &key, MHCommand op) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Executes microHIL command
    /// @param key represents command key in string format
    virtual void executeCommand(const std::string &key) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets supported commands
    /// @return command keys in string format
    virtual std::vector<std::string> getSupportedCommands() const = 0;
};
