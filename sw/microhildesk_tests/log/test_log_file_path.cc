/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test_log_file_path.cc
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
/// @brief Test setting the output file path
TEST_F(LogTest, SetOutputFileTest)
{
    std::string path = "subdir_test.log";
    
    // 1. Set the file path
    m_logger.setOutputFile(path);
    
    // 2. Verify indirectly by attempting to open the log
    // Your log.cc returns false if m_outputFile.empty()
    EXPECT_TRUE(m_logger.open());
    
    // 3. Verify the file actually exists on the filesystem
    EXPECT_TRUE(std::filesystem::exists(path));
    
    // Cleanup
    m_logger.close();
    std::filesystem::remove(path);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Test behavior when no file path is set
TEST_F(LogTest, EmptyFilePathTest)
{
    // Ensure path is empty (default state)
    // Your open() implementation: if (m_outputFile.empty()) { return false; }
    EXPECT_FALSE(m_logger.open());
}
