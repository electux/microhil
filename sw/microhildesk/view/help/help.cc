////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// help.cc
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
#include <string_view>
#include <view/help/help.h>

namespace {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application Help Window Widgets Parameters
    /// @{
    constexpr std::string_view cHelpTitle{"microhildesk - Documentation"};
    constexpr int cHelpWidth{640};
    constexpr int cHelpHeight{480};
    constexpr int cHelpMargin{12};
    constexpr std::string_view cHelpCloseButtonLabel{"Close"};
    constexpr int cHelpButtonWidth{100};
    constexpr int cHelpButtonHeight{36};

    constexpr std::string_view cHelpDocText{
        "<b><big>microHIL Desktop Control Application</big></b>\n\n"
        "<b>Overview:</b>\n"
        "microHIL is a Hardware-in-the-Loop (HIL) automation and test interface\n"
        "designed for controlling microHIL hardware devices (Raspberry Pi Pico,\n"
        "NuttX, and MicroPython firmware).\n\n"
        "<b>Channel Modes (Channels 1 - 8):</b>\n"
        "• <b>Toggle Mode:</b> Direct manual control to turn channels ON or OFF.\n"
        "• <b>Timer Mode:</b> Activates a channel for a specified duration in seconds.\n"
        "• <b>Pulse Mode:</b> Emits a single trigger pulse for a duration in milliseconds.\n"
        "• <b>Blink Mode:</b> Continuously toggles a channel with configurable ON and OFF durations (ms).\n\n"
        "<b>Batch &amp; Diagnostic Commands:</b>\n"
        "• <b>All Channels On / Off:</b> Global batch activation/deactivation across all 8 channels.\n"
        "• <b>All Status:</b> Synchronizes and queries real-time status of all 8 channels.\n"
        "• <b>System Reset (*RST):</b> Hardware reset to default safe state.\n"
        "• <b>Get Board ID (*IDN?):</b> Queries hardware identification string.\n"
        "• <b>Get Version:</b> Queries device firmware version information.\n\n"
        "<b>Communication Interfaces:</b>\n"
        "• <b>Serial Port:</b> POSIX RS-232 / USB CDC UART (baud rate, data bits, parity, stop bits, flow control).\n"
        "• <b>TCP/IP:</b> Network socket connection with configurable IP and Port.\n"
        "• <b>BLE:</b> Bluetooth Low Energy via BlueZ D-Bus with automatic service discovery.\n\n"
        "<b>Configuration &amp; Logging:</b>\n"
        "• Open <b>Option -&gt; Settings</b> to configure communication and log settings.\n"
        "• Configurable log levels: None, Error, Warning, Info, and Debug."
    };
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::View::Help;

AppHelp::AppHelp() {
    set_title(cHelpTitle.data());
    set_default_size(cHelpWidth, cHelpHeight);
    set_resizable(true);
    set_hide_on_close(true);

    m_boxMain.set_margin(cHelpMargin);
    set_child(m_boxMain);

    m_labelContent.set_markup(cHelpDocText.data());
    m_labelContent.set_wrap(true);
    m_labelContent.set_xalign(0.0f);
    m_labelContent.set_selectable(true);

    m_boxContent.append(m_labelContent);
    m_boxContent.set_margin(cHelpMargin);

    m_scrolledWindow.set_child(m_boxContent);
    m_scrolledWindow.set_vexpand(true);
    m_scrolledWindow.set_hexpand(true);
    m_boxMain.append(m_scrolledWindow);

    m_buttonClose.set_label(cHelpCloseButtonLabel.data());
    m_buttonClose.set_size_request(cHelpButtonWidth, cHelpButtonHeight);
    m_buttonClose.set_halign(Gtk::Align::END);
    m_buttonClose.signal_clicked().connect([this]() { hide(); });
    m_boxMain.append(m_buttonClose);
}

void AppHelp::show() { present(); }

Gtk::Window &AppHelp::getGtkWindow() { return *this; }
