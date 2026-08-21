////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings_setup.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <view/settings_setup.h>
#include <model/model.h>

namespace Electux::App::Model
{
	SettingsSetup::SettingsSetup()
		: m_config(std::make_unique<Model>())
	{}

	SettingsSetup::~SettingsSetup() = default;

	SettingsSetup::SettingsSetup(const SettingsSetup& other)
		: m_config(other.m_config ? other.m_config->clone() : nullptr)
	{}

	SettingsSetup& SettingsSetup::operator=(const SettingsSetup& other)
	{
		if (this != &other)
		{
			m_config = other.m_config ? other.m_config->clone() : nullptr;
		}
		return *this;
	}

	SettingsSetup::SettingsSetup(SettingsSetup&&) noexcept = default;
	SettingsSetup& SettingsSetup::operator=(SettingsSetup&&) noexcept = default;
}