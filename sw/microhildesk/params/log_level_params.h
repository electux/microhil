/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * log_level_params.h
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

#include <string_view>

namespace Electux::App::Params::LogLevels {
    /////////////////////////////////////////////////////////////////////////
    /// @brief Log levels parameters
    ///   cLogLevels - array of log level names
    ///   clogLevelError - index for Error level
    ///   clogLevelWarning - index for Warning level
    ///   clogLevelInfo - index for Info level
    constexpr std::string_view cLogLevels[]{"Error", "Warning", "Info"};
    constexpr const unsigned int clogLevelError = 0;
    constexpr const unsigned int clogLevelWarning = 1;
    constexpr const unsigned int clogLevelInfo = 2;
};
