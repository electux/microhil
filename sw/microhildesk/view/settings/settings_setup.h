/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_setup.h
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

#include <vector>
#include <glibmm/ustring.h>

namespace Electux::App::View::Settings
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Setup settings for collected parameters
    class SettingsSetup
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief SettingsSetup constructor
        inline SettingsSetup() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief SettingsSetup destructor
        inline ~SettingsSetup() noexcept = default;

        //////////////////////////////////////////////////////////////////////
        /// @brief Settings parameters
        ///   m_serialDevicePath - absolute path for serial device file
        ///   m_serialParams - baud, data, parity, stop parameters
        ///   m_logFilePath - absolute path for log file
        ///   m_logLevel - log level
        Glib::ustring m_serialDevicePath;
        std::vector<int> m_serialParams;
        Glib::ustring m_logFilePath;
        int m_logLevel;
    };
};

