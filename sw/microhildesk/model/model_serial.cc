/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model_serial.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "model_serial.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for serial configuration keys
    constexpr const char device[]{"device"};
    constexpr const char baud[]{"baud"};
    constexpr const char data[]{"data"};
    constexpr const char parity[]{"parity"};
    constexpr const char stop[]{"stop"};
    constexpr const char unknown[]{"unknown"};
};

using namespace Electux::App::Model;

std::string ModelSerial::to_string(Key key)
{
    switch (key)
    {
    case Key::Device: return device;
    case Key::Baud: return baud;
    case Key::Data: return data;
    case Key::Parity: return parity;
    case Key::Stop: return stop;
    default: return unknown;
    }
}
