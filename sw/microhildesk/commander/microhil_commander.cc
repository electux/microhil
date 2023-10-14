/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_commander.h
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_commander.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL command for getting HW id
    constexpr const char kId[]{"<mh#ch#id#end>"};

    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL command for getting FW version
    constexpr const char kVersion[]{"<mh#ch#version#end>"};

    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL channel control begin
    constexpr const char kChannelBegin[]{"<mh#ch#"};

    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL all channels control begin
    constexpr const char kChannelsBegin[]{"<mh#ch#all#"};

    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL hash
    constexpr const char kHash[]{"#"};

    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL control end
    constexpr const char kEnd[]{"#end>"};
} // namespace

MHCommander::MHCommander(SPtr<IMHCom> serial)
    : m_serial{serial}
{
}

void MHCommander::executeCommand(const int id, const std::string &onoff)
{
    switch (id)
    {
    case 0:
        getId();
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        setChannel(id, onoff);
        break;
    case 9:
        setAllChannel(onoff);
        break;
    case 10:
        getVersion();
        break;
    default:;
    }
}

void MHCommander::getId()
{
    std::string command = kId;
    const VecByte data(command.begin(), command.end());
    m_serial->write(data);
}

void MHCommander::getVersion()
{
    std::string command = kVersion;
    const VecByte data(command.begin(), command.end());
    m_serial->write(data);
}

void MHCommander::setChannel(const int id, const std::string &onoff)
{
    std::string command;
    command.append(kChannelBegin);
    command.append(std::to_string(id));
    command.append(kHash);
    command.append(onoff);
    command.append(kEnd);
    const VecByte data(command.begin(), command.end());
    m_serial->write(data);
}

void MHCommander::setAllChannel(const std::string &onoff)
{
    std::string command;
    command.append(kChannelsBegin);
    command.append(onoff);
    command.append(kEnd);
    const VecByte data(command.begin(), command.end());
    m_serial->write(data);
}
