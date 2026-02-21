/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_config.h
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

#include <gtest/gtest.h>
#include <config/config_manager.h>

namespace Electux::App::Config
{
    ///////////////////////////////////////////////////////////////////////////
    /// @brief Proxy class to expose protected ConfigManager methods for testing
    class ConfigManagerProxy : public ConfigManager
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Promoting protected methods to public for unit testing
        using ConfigManager::defaultConfigStore;
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fixture for ConfigManager tests
    class ConfigManagerTest : public ::testing::Test
    {
    protected:
        using ConfigManager = Electux::App::Config::ConfigManagerProxy;

        ConfigManager m_config{};

        void SetUp() override
        {
            // Initialization if necessary
        }

        void TearDown() override
        {
            // Cleanup if necessary
        }
    };
}

