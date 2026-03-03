////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings_map.cc
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

#include <view/settings/settings.h>

using namespace Electux::App::View::Settings;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Maps signals to slots for the settings dialog widgets.
///
/// Connects the clicked signals of the OK and Cancel buttons to their
/// respective handlers within the AppSettings class to manage dialog actions.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::mapping()
{
	// Maps signals to slots (widget actions for settings dialog)
	m_buttonOk.signal_clicked().connect(
		sigc::mem_fun(*this, &AppSettings::onButtonOkClicked)
	);

	m_buttonCancel.signal_clicked().connect(
		sigc::mem_fun(*this, &AppSettings::onButtonCancelClicked)
	);
}
