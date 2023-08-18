/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_dialog_abstract.h
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

#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped enumerator for dialog message types
enum class MessageType
{
    INFO = 0,
    WARNING = 1,
    ERROR = 2
};

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewDialog class declaration and definition
class AbMicroHILViewDialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for dialog Close button
    using closeDialog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewDialog destructor
    virtual ~AbMicroHILViewDialog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signals for emitting from dialog Close button
    /// @return signal after pressing Close button
    virtual closeDialog closeDialogChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slots for processing Close button for dialog
    virtual void onCloseDialogChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Show dialog with message
    /// @param message for presenting
    /// @param type of dialog message
    virtual void show(Glib::ustring message, MessageType type) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Hide dialog
    virtual void hide() = 0;
};
