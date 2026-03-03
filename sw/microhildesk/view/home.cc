////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home.cc
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

#include <string>
#include <format>
#include <view/home.h>
#include <params/channel_params.h>

namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Application Home Window Widgets Parameters
	/// @{
	constexpr std::string_view cHomeTitle{"microhildesk"};
	constexpr int cHomeWidth{600};
	constexpr int cHomeHeight{250};
	constexpr std::string_view cHomeEnChannelLabel{"Enable Channel #"};
	constexpr std::string_view cHomeToggleChannelLabel{"Toogle Channel #"};
	constexpr std::string_view cHomeToggleChannelButtonActivate{"Activate"};
	constexpr std::string_view cHomeToggleChannelButtonDeactivate{"Deactivate"};
	constexpr std::string_view cHomeTimerChannelLabel{"Use timer #"};
	constexpr std::string_view cHomeTimerChannelButtonStart{"Start"};
	constexpr std::string_view cHomeTimerChannelButtonStop{"Stop"};
	constexpr float cHomeStatusFraction{0.0};
	constexpr int cHomeBoxChannelMargin{10};
	constexpr int cHomeBoxChannelSpacing{5};
	constexpr std::string_view cHomeChannelModeOptions[]{"Toogle Active", "Timer Active"};
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::View;
using namespace Electux::App::Params::Channel;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief AppHome constructor.
///
/// Sets up the main window properties, initializes layout containers, and
/// dynamically creates UI widgets for each channel based on defined parameters.
////////////////////////////////////////////////////////////////////////////////////////////////////////
AppHome::AppHome()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Setup application home window
	set_title(cHomeTitle.data());
	set_default_size(cHomeWidth, cHomeHeight);
	set_resizable(false);
	set_show_menubar(true);
	m_boxRoot.set_orientation(Gtk::Orientation::HORIZONTAL);
	set_child(m_boxRoot);

	for (ssize_t i = 0; i < cNumOfChannels; i++)
	{
		m_boxChannels.emplace_back(Gtk::Orientation::VERTICAL);
		auto& currentBox = m_boxChannels.back();

		// Setup Enable CheckButton
		m_enableChannels.emplace_back(std::format("{} {}", cHomeEnChannelLabel.data(), i));
		currentBox.append(m_enableChannels.back());

		// Setup Mode ComboBox
		m_selectControlChannels.emplace_back();
		for (const auto& option : cHomeChannelModeOptions)
		{
			m_selectControlChannels.back().append(option.data());
		}
		currentBox.append(m_selectControlChannels.back());

		// Setup Toggle Label and Button
		m_labelToggleChannels.emplace_back(std::format("{} {}", cHomeToggleChannelLabel.data(), i));
		currentBox.append(m_labelToggleChannels.back());
		m_toggleChannels.emplace_back();
		m_toggleChannels.back().set_label(cHomeToggleChannelButtonActivate.data());
		currentBox.append(m_toggleChannels.back());

		// Setup Timer Label, Spinner and Button
		m_labelTimerChannels.emplace_back(std::format("{} {}", cHomeTimerChannelLabel.data(), i));
		currentBox.append(m_labelTimerChannels.back());
		m_spinTimerChannels.emplace_back();
		m_spinTimerChannels.back().set_range(0.0, 3600.0);
		m_spinTimerChannels.back().set_increments(1.0, 10.0);
		currentBox.append(m_spinTimerChannels.back());
		m_toggleTimerChannels.emplace_back();
		m_toggleTimerChannels.back().set_label(cHomeTimerChannelButtonStart.data());
		currentBox.append(m_toggleTimerChannels.back());

		// Setup Progress Bar
		m_statusTimerChannels.emplace_back();
		m_statusTimerChannels.back().set_fraction(cHomeStatusFraction);
		currentBox.append(m_statusTimerChannels.back());

		// Layout and Signal Mapping
		currentBox.set_margin(cHomeBoxChannelMargin);
		currentBox.set_spacing(cHomeBoxChannelSpacing);
		m_boxRoot.append(currentBox);
		mapping(i);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the internal configuration setup.
/// @param setup Constant reference to the SettingsSetup object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppHome::setControlSetup(const SettingsSetup& setup)
{
	m_setup = setup;
}
