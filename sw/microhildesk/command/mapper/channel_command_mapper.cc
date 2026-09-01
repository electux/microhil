////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_command_mapper.cc
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
#include <command/mapper/channel_command_mapper.h>
#include <format>
#include <string_view>

using namespace Electux::App::Command;

namespace {
    constexpr std::string_view cLogChannelDisabled{"Channel {} disabled"};
    constexpr std::string_view cCmdChannelOff{"<mh#ch#{}#off#end>"};
    constexpr std::string_view cLogChannelStateChanged{
        "Channel {} state changed: enabled={}, mode={}, toggle={}, timer={}, timerEnabled={}"
    };
    constexpr std::string_view cLogPulseTriggered{
        "Channel {} pulse triggered: duration={}ms"
    };
    constexpr std::string_view cLogBlinkStateChanged{
        "Channel {} blink state changed: enabled={}, on={}ms, off={}ms, count={}"
    };
} // namespace

ChannelMappingResult ChannelCommandMapper::map(
    size_t channelIndex,
    const Model::Channel::ChannelState &state,
    const ICommandFormatter &formatter
) const {
    ChannelMappingResult result;

    if (!state.enabled) {
        result.logMessage = std::format(cLogChannelDisabled, channelIndex);
        result.command = std::format(cCmdChannelOff, channelIndex + 1);
        return result;
    }

    if (state.mode == Model::Channel::ChannelMode::Toggle ||
        state.mode == Model::Channel::ChannelMode::Timer) {
        result.logMessage = std::format(
            cLogChannelStateChanged,
            channelIndex, state.enabled, static_cast<int>(state.mode),
            state.toggle, state.timer, state.timerEnabled
        );
        result.command = formatter.getCommandState(channelIndex, state);
    } else if (state.mode == Model::Channel::ChannelMode::Pulse) {
        if (state.pulseTriggered) {
            result.logMessage = std::format(
                cLogPulseTriggered,
                channelIndex, state.pulseTime
            );
            result.command = formatter.getCommandPulse(channelIndex, state);
        } else {
            result.command = std::format(cCmdChannelOff, channelIndex + 1);
        }
    } else if (state.mode == Model::Channel::ChannelMode::Blink) {
        result.logMessage = std::format(
            cLogBlinkStateChanged,
            channelIndex, state.blinkEnabled, state.blinkOnTime,
            state.blinkOffTime, state.blinkCount
        );
        if (state.blinkEnabled) {
            result.command = formatter.getCommandBlink(channelIndex, state);
        } else {
            result.command = std::format(cCmdChannelOff, channelIndex + 1);
        }
    }

    return result;
}
