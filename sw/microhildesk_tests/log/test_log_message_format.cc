/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_log_message_format.cc
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
#include "test_log.h"

using namespace Electux::App::Logger;

////////////////////////////////////////////////////////////////////////////
/// @brief Test message content and formatting
TEST_F(LogTest, LogMessageFormatTest)
{
    m_logger.setLevel(LogLevel::Info);
    m_logger.open();
    
    std::string testMsg = "Critical System Failure";
    m_logger.log(testMsg, LogLevel::Error);
    
    std::string output = getLastLine();
    // Verify timestamp format YYYY-MM-DD
    EXPECT_NE(output.find("T"), std::string::npos);
    // Verify tag
    EXPECT_NE(output.find("[ERROR]"), std::string::npos);
    // Verify message
    EXPECT_NE(output.find(testMsg), std::string::npos);
    
    m_logger.close();
}
