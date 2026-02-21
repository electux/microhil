/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_log.h
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
#include <log/log.h>
#include <filesystem>

namespace Electux::App::Logger
{
    ///////////////////////////////////////////////////////////////////////////
    /// @brief Proxy class to inspect internal Log state
    class LogProxy : public Log {
    public:
        // Helper to check the internal file path since m_outputFile is private
        // but accessible to this derived class if we change it to protected.
        // NOTE: In your current log.h, m_outputFile is PRIVATE. 
        // To test it directly, you must change it to PROTECTED in log.h.
        std::string getFilePath() const {
            // This works ONLY if m_outputFile is moved to 'protected' in log.h
            // Otherwise, we must test setOutputFile indirectly via open().
            return ""; 
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fixture for Log tests
    class LogTest : public ::testing::Test
    {
    protected:
        using Log = Electux::App::Logger::Log;
        using LogLevel = Electux::App::Logger::ILog::LogLevel;

        Log m_logger{};
        const std::string m_testFileName = "test_output.log";

        void SetUp() override
        {
            if (std::filesystem::exists(m_testFileName))
            {
                std::filesystem::remove(m_testFileName);
            }

            m_logger.setOutputFile(m_testFileName);
        }

        void TearDown() override
        {
            m_logger.close();
            if (std::filesystem::exists(m_testFileName))
            {
                std::filesystem::remove(m_testFileName);
            }
        }

        ///////////////////////////////////////////////////////////////////////////
        /// @brief Helper to read the last line of the log file
        std::string getLastLine()
        {
            std::ifstream file(m_testFileName);
            std::string line, lastLine;

            while (std::getline(file, line))
            {
                if (!line.empty()) lastLine = line;
            }

            return lastLine;
        }
    };

};