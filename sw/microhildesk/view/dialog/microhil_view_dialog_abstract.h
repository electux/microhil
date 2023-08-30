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
/// @brief Scoped class enumerator for dialog message types
enum class MessageType
{
    MICROHIL_INFO = 0,
    MICROHIL_WARNING = 1,
    MICROHIL_ERROR = 2
};

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewDialog class declaration and definition
class AbMicroHILViewDialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Close button (self hide Dialog signal)
    using SigHideDialog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewDialog destructor
    virtual ~AbMicroHILViewDialog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Close button
    /// @return Signal for clicked Close button
    virtual SigHideDialog hideDialogTrigered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Close button (self hide Dialog)
    virtual void onHideDialogTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set message for dialog
    /// @param message with information for user
    /// @param type of dialog message
    virtual void setMessage(
        const Glib::ustring message, const MessageType type
    ) = 0;
};
