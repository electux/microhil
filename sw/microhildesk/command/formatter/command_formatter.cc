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

#include <command/formatter/command_formatter.h>
#include <format>

using namespace Electux::App::Command;

std::string CommandFormatter::getCommandState(
    size_t channelIdx, const Model::Channel::ChannelState &state
) const {
    if (!state.enabled) {
        return std::format("<mh#ch#{}#off#end>", channelIdx + 1);
    }

    if (state.mode == Model::Channel::ChannelMode::Toggle) // Toggle Mode
    {
        return std::format(
            "<mh#ch#{}#{}#end>", channelIdx + 1, state.toggle ? "on" : "off"
        );
    }

    if (state.mode == Model::Channel::ChannelMode::Timer) // Timer Mode
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

std::string CommandFormatter::getCommandPulse(
    size_t channelIdx, const Model::Channel::ChannelState &state
) const {
    return std::format("<mh#ch#{}#pulse#{}#end>", channelIdx + 1, state.pulseTime);
}

std::string CommandFormatter::getCommandBlink(
    size_t channelIdx, const Model::Channel::ChannelState &state
) const {
    return std::format(
        "<mh#ch#{}#blink#{}#{}#{}#end>",
        channelIdx + 1,
        state.blinkOnTime,
        state.blinkOffTime,
        state.blinkCount
    );
}

std::string CommandFormatter::getCommandOffAllChannels() const {
    return "<mh#all#off#end>";
}

std::string CommandFormatter::getCommandOnAllChannels() const {
    return "<mh#all#on#end>";
}

std::string CommandFormatter::getCommandMaskChannels(
    const std::vector<Model::Channel::ChannelState> &states
) const {
    std::string command = "<mh#all#mask#";
    for (const auto &state : states) {
        command += (state.enabled and state.toggle ? "1" : "0");
    }
    command += "#end>";
    return command;
}

std::string CommandFormatter::getCommandStatus(size_t channelIdx) const {
    return std::format("<mh#ch#{}#stat#end>", channelIdx + 1);
}

std::string CommandFormatter::getCommandStatusAllChannels() const {
    return "<mh#all#stat#end>";
}

std::string CommandFormatter::getCommandReset() const {
    return "<mh#sys#reset#end>";
}

std::string CommandFormatter::getCommandBoardId() const {
    return "<mh#sys#id#end>";
}

std::string CommandFormatter::getCommandVersion() const {
    return "<mh#sys#version#end>";
}
