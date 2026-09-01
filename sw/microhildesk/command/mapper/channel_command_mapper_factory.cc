////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_command_mapper_factory.cc
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
#include <command/mapper/channel_command_mapper_factory.h>

namespace Electux::App::Command {
    std::unique_ptr<IChannelCommandMapper> createChannelCommandMapper() {
        return std::make_unique<ChannelCommandMapper>();
    }
} // namespace Electux::App::Command
