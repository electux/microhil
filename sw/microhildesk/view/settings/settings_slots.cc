////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings_slots.cc
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
/// @brief Performs action on OK button click.
/// 
/// Saves data to configuration and emits the setupChanged signal.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::onButtonOkClicked()
{
	getUiData();
	m_setupSignal.emit(m_setup);
	hide();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Performs action on Cancel button click.
/// 
/// Hides the settings window without saving any changes.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppSettings::onButtonCancelClicked()
{
	hide();
}
