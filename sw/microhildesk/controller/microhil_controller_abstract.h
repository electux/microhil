/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_controller_abstract.h
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

////////////////////////////////////////////////////////////////////////////
/// @brief AbMHController class declaration and definition
class AbMHController
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMHController destructor
    virtual ~AbMHController() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable controller (enable/disable communication)
    /// @param switchController request value
    virtual void setEnabled(bool switchController) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check is controller enabled (is serial communication enabled)
    /// @return boolean status true for enabled else false
    virtual bool isEnabled() const = 0;
};
