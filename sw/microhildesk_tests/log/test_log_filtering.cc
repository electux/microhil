/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_log_filtering.cc
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
/// @brief Test log filtering based on level
TEST_F(LogTest, LogFilteringTest)
{
    m_logger.setLevel(LogLevel::Error);
    m_logger.open();

    // This should be filtered out because level is Info (2) > Error (0)
    m_logger.log("This should not appear", LogLevel::Info);
    
    // File should be empty
    std::ifstream file(m_testFileName);
    EXPECT_EQ(file.peek(), std::ifstream::traits_type::eof());
    
    m_logger.close();
}
