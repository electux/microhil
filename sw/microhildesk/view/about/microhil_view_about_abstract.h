/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_about_abstract.h
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

#include <sigc++/sigc++.h>

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewAbout class declaration and definition 
class AbMicroHILViewAbout
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Ok button (self hide AboutDialog signal)
    using hideAbout = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewAbout destructor
    virtual ~AbMicroHILViewAbout() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    virtual hideAbout hideAboutTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button (self hide AboutDialog)
    virtual void onHideAboutTriggered() = 0;
};
