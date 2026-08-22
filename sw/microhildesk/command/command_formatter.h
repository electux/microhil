////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// command_formatter.h
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

#include <command/icommand_formatter.h>

namespace Electux::App::Command {
////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class CommandFormatter
/// @brief Implements ICommandFormatter to serialize relay channel state into
/// command strings.
////////////////////////////////////////////////////////////////////////////////////////////////////
class CommandFormatter : public ICommandFormatter {
public:
  CommandFormatter() = default;
  virtual ~CommandFormatter() override = default;

  CommandFormatter(const CommandFormatter &) = delete;
  CommandFormatter &operator=(const CommandFormatter &) = delete;

  virtual std::string
  getCommandState(size_t channelIdx,
                  const Model::Channel::ChannelState &state) const override;
};
} // namespace Electux::App::Command
