/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_types.h
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
#pragma once

#include <cstdint>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <memory>
#include <vector>

////////////////////////////////////////////////////////////////////////////
/// Shortest shared pointer declaration
template <typename T> using RPtr = Glib::RefPtr<T>;

////////////////////////////////////////////////////////////////////////////
/// Shortest shared pointer declaration
template <typename T> using SPtr = std::shared_ptr<T>;

////////////////////////////////////////////////////////////////////////////
/// Creating shorted pointer
template <typename T, typename... Args> SPtr<T> makeSPtr(Args... args)
{
    return std::make_shared<T>(args...);
}

////////////////////////////////////////////////////////////////////////////
/// Shortest unique pointer declaration
template <typename T> using UPtr = std::unique_ptr<T>;

////////////////////////////////////////////////////////////////////////////
/// Creating unique pointer
template <typename T, typename... Args> UPtr<T> makeUPtr(Args... args)
{
    return std::make_unique<T>(args...);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Declared type vector of int elements
using VecUInt = std::vector<unsigned int>;

////////////////////////////////////////////////////////////////////////////
/// @brief Declared type vector of uint8_t elements
using VecByte = std::vector<uint8_t>;

////////////////////////////////////////////////////////////////////////////
/// @brief Declared Glib unicode string type
using UString = Glib::ustring;
