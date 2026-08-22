////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// command_formatter.cc
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

#include <command/command_formatter.h>
#include <format>

using namespace Electux::App::Command;

std::string CommandFormatter::getCommandState(
    size_t channelIdx, const Model::Channel::ChannelState &state
) const {
    if (!state.enabled) {
        return std::format("<mh#ch#{}#off#end>", channelIdx + 1);
    }
    if (state.mode == 0) // Toggle Mode
    {
        return std::format(
            "<mh#ch#{}#{}#end>", channelIdx + 1, state.toggle ? "on" : "off"
        );
    } else if (state.mode == 1) // Timer Mode
    {
        if (state.timerEnabled) {
            return std::format(
                "<mh#ch#{}#tmr#{}#end>", channelIdx + 1, state.timer
            );
        } else {
            return std::format("<mh#ch#{}#off#end>", channelIdx + 1);
        }
    }
    return "";
}
