////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ichannel_command_mapper.h
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
#pragma once

#include <command/formatter/icommand_formatter.h>
#include <model/channel_state.h>
#include <string>

namespace Electux::App::Command {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @struct ChannelMappingResult
    /// @brief Result of mapping a channel state to a command string and a log message.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    struct ChannelMappingResult {
        std::string command;
        std::string logMessage;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IChannelCommandMapper
    /// @brief Interface for translating channel states to device commands and log messages.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IChannelCommandMapper {
      public:
        virtual ~IChannelCommandMapper() = default;

        virtual ChannelMappingResult map(
            size_t channelIndex,
            const Model::Channel::ChannelState &state,
            const ICommandFormatter &formatter
        ) const = 0;
    };
} // namespace Electux::App::Command
