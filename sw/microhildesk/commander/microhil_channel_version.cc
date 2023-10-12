/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_channel_version.cc
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
#include "microhil_channel_version.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// microHIL command for getting version
    constexpr const char kGetVersion[]{"<mh#ch#version#end>"};
} // namespace

ChannelVersion::ChannelVersion(SPtr<IMHCom> serial)
    : m_serial{serial}
{
}

void ChannelVersion::getVersion(const std::string &command)
{
    const VecByte data(command.begin(), command.end());
    m_serial->write(data);
}
