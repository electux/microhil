////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_store.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include "test_config.h"

using namespace Electux::App::Config;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the storage functionality of ConfigManager.
///
/// Verifies that the configuration manager can successfully serialize internal
/// settings and write them to a file. Checks for file creation and ensures
/// that the resulting file contains data.
///
/// @param ConfigManagerTest The test fixture.
/// @param StoreConfigTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, StoreConfigTest)
{
	bool success = m_config->store();

	EXPECT_TRUE(success);
	EXPECT_TRUE(std::filesystem::exists(m_testConfigFileName));
	EXPECT_GT(std::filesystem::file_size(m_testConfigFileName), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test store functionality when file permissions prevent writing.
///
/// Creates a temporary configuration file, removes write permissions, and verifies
/// that the store() method fails gracefully without crashing. Restores permissions
/// afterward to allow cleanup.
///
/// @param ConfigManagerTest The test fixture.
/// @param StoreFailureTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, StoreFailureTest)
{
	// Create a dummy file and remove write permissions
	{
		std::ofstream ofs(m_testConfigFileName);
		ofs << "data=1\n";
	}

	chmod(m_testConfigFileName.c_str(), S_IRUSR); // Read only

	EXPECT_FALSE(m_config->store());

	chmod(m_testConfigFileName.c_str(), S_IWUSR | S_IRUSR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test that defaultConfigStore resets values to defaults.
///
/// Creates a temporary configuration file, removes write permissions, and verifies
/// that the store() method fails gracefully without crashing. Restores permissions
/// afterward to allow cleanup.
///
/// @param ConfigManagerTest The test fixture.
/// @param ExplicitDefaultStoreTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, ExplicitDefaultStoreTest)
{
	m_config->init();
	auto serial = m_config->getConfig();
	const auto deviceKey = serial.toString(ModelSerialKey::Device);

	serial.add(deviceKey, "/dev/custom_path");
	m_config->defaultConfigStore();

	EXPECT_EQ(serial.getEntity(deviceKey), "/dev/ttyUSB0");
}
