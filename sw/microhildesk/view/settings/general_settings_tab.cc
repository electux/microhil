////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// general_settings_tab.cc
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <view/settings/general_settings_tab.h>
#include <string>

namespace
{
	constexpr std::string_view cSettingsComTypeLabel{"Connection type"};
	constexpr std::string_view cComTypeSerial{"Serial Port"};
	constexpr std::string_view cComTypeTcp{"TCP/IP Connection"};
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Model;

GeneralSettingsTab::GeneralSettingsTab()
	: Gtk::Box(Gtk::Orientation::VERTICAL)
{
	m_labelComType.set_label(cSettingsComTypeLabel.data());
	append(m_labelComType);

	m_comboComType.append(cComTypeSerial.data());
	m_comboComType.append(cComTypeTcp.data());
	append(m_comboComType);
}

void GeneralSettingsTab::updateData(const IModel &config)
{
	auto comTypeKey = config.toString(ModelGeneralKey::ComType);
	auto value = config.getEntity(comTypeKey);

	if (value == "tcp")
	{
		m_comboComType.set_active(1);
	}
	else
	{
		m_comboComType.set_active(0);
	}
}

void GeneralSettingsTab::getData(IModel &config)
{
	auto comTypeKey = config.toString(ModelGeneralKey::ComType);
	int active = m_comboComType.get_active_row_number();

	if (active == 1)
	{
		config.update(comTypeKey, "tcp");
	}
	else
	{
		config.update(comTypeKey, "serial");
	}
}
