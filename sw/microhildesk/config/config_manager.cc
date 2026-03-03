////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_manager.cc
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

#include <glibmm/miscutils.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <config/config_manager.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Configuration Constants
	/// @{
	// Default values for Control Model
	constexpr std::string_view cConfigFile{".microhil/config"};
	// Delimiter for key-value pairs in the config file
	constexpr char cConfigAssignDelimiter{'='};
    // Character indicating a comment line in the config file
	constexpr char cConfigCommentChar{'#'};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::Config;
using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructor that initializes the config path.
/// @param configFileName The path/name of the configuration file.
////////////////////////////////////////////////////////////////////////////////////////////////////////
ConfigManager::ConfigManager(const std::string &configFileName) noexcept
{
	m_fileName = configFileName.empty() ? Glib::build_filename(Glib::get_home_dir(), cConfigFile.data()) : configFileName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Initializes the configuration manager.
/// Performs file system checks, directory creation, and initial load.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::init()
{
	auto dirPath = Glib::path_get_dirname(m_fileName);

	try
	{
		if (!std::filesystem::exists(dirPath))
		{
			std::filesystem::create_directories(dirPath);
		}

		if (!std::filesystem::exists(m_fileName))
		{
			{
				std::ofstream file(m_fileName);
				if (!file)
				{
					throw std::ios_base::failure("Unable to create file: " + m_fileName);
				}

				// File closes here when going out of scope, releasing the handle before store()
			}
			defaultConfigStore();
		}

		std::cout << "Initialized configuration file path: " << m_fileName << std::endl;
		load();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error during ConfigManager initialization: " << e.what() << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Parses the configuration file line by line.
///
/// Skips comments and empty lines. Validates keys against models.
/// @return true if the configuration was successfully loaded, else false.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConfigManager::load()
{
	std::ifstream file(m_fileName);
	std::cout << "Loading configuration..." << std::endl;

	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << m_fileName << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		// Skip empty lines and comments
		if (line.empty() || line[0] == cConfigCommentChar)
		{
			continue;
		}

		std::istringstream iss(line);
		std::string key, value;

		if (std::getline(iss, key, cConfigAssignDelimiter) && std::getline(iss, value))
		{
			// Trim whitespace
			key.erase(0, key.find_first_not_of(" \t\n\r"));
			key.erase(key.find_last_not_of(" \t\n\r") + 1);
			value.erase(0, value.find_first_not_of(" \t\n\r"));
			value.erase(value.find_last_not_of(" \t\n\r") + 1);

			// Map keys to specific models
			if (m_config.validateKey(key))
			{
				m_config.add(key, value);
			}
			else
			{
				std::cerr << "Warning: Unknown configuration key: " << key << std::endl;
				continue;
			}
		}
	}

	file.close();
	std::cout << "Load configuration done." << std::endl;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Serializes all models and writes them to the configuration file.
/// @return true if the configuration was successfully stored, else false.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConfigManager::store()
{
	std::ofstream file(m_fileName);
	std::cout << "Storing configuration..." << std::endl;

	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << m_fileName << std::endl;
		return false;
	}

	// Internal helper lambda for writing model entries
	auto writeModel = [&](const auto& model)
	{
		for (const auto& [key, value] : model.getAllEntries())
		{
			file << key << cConfigAssignDelimiter << value << "\n";
		}
	};

	writeModel(m_config);

	file.close();
	std::cout << "Store configuration done." << std::endl;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the control configuration.
/// @param config Reference to the Model configuration object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::setConfig(const Model& config)
{
	m_config = config;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets the current control configuration.
/// @return A constant reference to the Model configuration.
////////////////////////////////////////////////////////////////////////////////////////////////////////
const Model& ConfigManager::getConfig() const
{
	return m_config;
}

