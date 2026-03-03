////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// model.cc
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

#include <algorithm>
#include <initializer_list>
#include <vector>
#include <model/model.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Model
/// @brief Namespace for application data models and entities
namespace Electux::App::Model
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Fallback string for getEntity method when key is not found
	////////////////////////////////////////////////////////////////////////////////////////////////////
	constexpr std::string_view cFallback{""};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Control Key Constants
	/// @{
	constexpr std::string_view cEnable{"enable"};           ///< String key for enable
	constexpr std::string_view cMode{"mode"};               ///< String key for mode
	constexpr std::string_view cToggle{"toggle"};           ///< String key for toggle
	constexpr std::string_view cTimer{"timer"};             ///< String key for timer
	constexpr std::string_view cTimerEnable{"timerEnable"}; ///< String key for timer enable
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Serial Key Constants
	/// @{
	constexpr std::string_view cDevice{"device"};           ///< String key for device
	constexpr std::string_view cBaud{"baud"};               ///< String key for baud rate
	constexpr std::string_view cData{"data"};               ///< String key for data bits
	constexpr std::string_view cParity{"parity"};           ///< String key for parity
	constexpr std::string_view cStop{"stop"};               ///< String key for stop bits
	constexpr std::string_view cFlow{"flow"};               ///< String key for flow control
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Log Key Constants
	/// @{
	constexpr std::string_view cLogLevel{"log_level"};      ///< String key for log level
	constexpr std::string_view cFilePath{"log_file_path"};  ///< String key for file path
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Internal Key Constants
	/// @{
	constexpr std::string_view cUnknown{"unknown"};         ///< Fallback for unknown keys
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Electux::App::Model

using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Adds an entity to the model.
/// @param key Represents the model entity key to be added.
/// @param data Represents the model entity data to be added.
/// @return true if the entity was successfully added, false if it already exists.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Model::add(const std::string_view &key, const std::string_view &data)
{
	if (m_entities.find(key) != m_entities.end())
	{
		return false;
	}

	auto [it, inserted] = m_entities.emplace(std::string(key), std::string(data));
		
	return inserted;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Validates if a string key is a valid control configuration key.
/// @param key Represents the string key to be validated.
/// @return true if the key matches one of the internal constants, else false.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Model::validateKey(const std::string_view &key) const
{
    static const std::initializer_list<std::string_view> validKeys =
	{
        cEnable, cMode, cToggle, cTimer, cTimerEnable,
        cLogLevel, cFilePath,
        cDevice, cBaud, cData, cParity, cStop, cFlow
    };

    return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) { return k == key; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets an entity value by its key.
/// @param key Represents the model entity key.
/// @return Reference to the string entity selected by key, or fallback if not found.
////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string &Model::getEntity(const std::string_view &key) const
{
	auto it = m_entities.find(key);
	if (it != m_entities.end())
	{
		return it->second;
	}

	static const std::string fallback{cFallback.data(), cFallback.size()};
	return fallback;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets all model entities.
/// @return Constant reference to the internal map of entities.
////////////////////////////////////////////////////////////////////////////////////////////////////////
const Entities &Model::get() const
{
	return m_entities;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets a copy of all control model entries.
///
/// Iterates through all defined ModelControlKey values and retrieves their
/// current string data from the underlying map.
/// @return A map containing all control configuration entries {key: data}.
////////////////////////////////////////////////////////////////////////////////////////////////////////
Entities Model::getAllEntries() const 
{
    Entities entries;

    auto fill = [&](auto&& keys)
	{
        for (const auto& key : keys)
		{
            std::string keyStr{toString(key)};
            entries.emplace(std::move(keyStr), getEntity(keyStr)); 
        }
    };

    static const std::vector<ModelControlKey> controlKeys =
	{
        ModelControlKey::Enable,
        ModelControlKey::Mode,
        ModelControlKey::Toggle,
        ModelControlKey::Timer,
        ModelControlKey::TimerEnable
    };

    static const std::vector<ModelLogKey> logKeys =
	{
        ModelLogKey::LogLevel, 
        ModelLogKey::FilePath
    };

    static const std::vector<ModelSerialKey> serialKeys =
	{
        ModelSerialKey::Device,
        ModelSerialKey::Baud,
        ModelSerialKey::Data,
        ModelSerialKey::Parity,
        ModelSerialKey::Stop,
        ModelSerialKey::Flow
    };

    fill(controlKeys);
    fill(logKeys);
    fill(serialKeys);

    return entries;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Updates an entity value by its key.
/// @param key Represents the model entity key.
/// @param data Represents the new value for the entity.
/// @return true if the entity was updated, false if the key does not exist.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Model::update(const std::string_view &key, const std::string_view &data)
{
	auto it = m_entities.find(key);
	if (it != m_entities.end())
	{
		it->second = data;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Clears all entities from the internal storage.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Model::clear()
{
	m_entities.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts a ModelControlKey enum value to its string representation.
/// @param key Represents the ModelControlKey enum value.
/// @return A string_view containing the constant key name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view Model::toString(const ModelControlKey &key) const
{
	switch (key)
	{
		case ModelControlKey::Enable:      return cEnable;
		case ModelControlKey::Mode:        return cMode;
		case ModelControlKey::Toggle:      return cToggle;
		case ModelControlKey::Timer:       return cTimer;
		case ModelControlKey::TimerEnable: return cTimerEnable;
		default:                           return cUnknown;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts a ModelLogKey enum value to its string representation.
/// @param key Represents the ModelLogKey enum value.
/// @return A string_view containing the constant key name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view Model::toString(const ModelLogKey &key) const
{
	switch (key)
	{
		case ModelLogKey::LogLevel: return cLogLevel;
		case ModelLogKey::FilePath: return cFilePath;
		default:                    return cUnknown;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Converts a ModelSerialKey enum value to its string representation.
/// @param key Represents the ModelSerialKey enum value.
/// @return A string_view containing the constant key name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view Model::toString(const ModelSerialKey &key) const
{
	switch (key)
	{
		case ModelSerialKey::Device: return cDevice;
		case ModelSerialKey::Baud:   return cBaud;
		case ModelSerialKey::Data:   return cData;
		case ModelSerialKey::Parity: return cParity;
		case ModelSerialKey::Stop:   return cStop;
		case ModelSerialKey::Flow:   return cFlow;
		default:                     return cUnknown;
	}
}
