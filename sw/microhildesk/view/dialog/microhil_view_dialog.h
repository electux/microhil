/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_dialog.h
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

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/dialog.h>
#include "microhil_view_dialog_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILViewDialog class declaration and definition 
class MicroHILViewDialog: public AbMicroHILViewDialog, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewDialog constructor
    /// @param object base object type
    /// @param ui builder parser
    MicroHILViewDialog(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewDialog destructor
    ~MicroHILViewDialog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signals for emitting from dialog Close button
    /// @return signal after pressing Close button
    closeDialog closeDialogChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slots for processing Close button for dialog
    void onCloseDialogChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Show dialog with message
    /// @param message for presenting
    /// @param type of dialog message
    void show(const Glib::ustring message, MessageType type) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Hide dialog
    void hide() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Conversion of message type to unicode string
    /// @param type of dialog message
    /// @return string representation of dialog message type
    Glib::ustring toUnicodeStringMessageType(MessageType type) const;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Map Close button signal and slot
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dialog message text filed
    Glib::RefPtr<Gtk::Label> m_text;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Close button for dialog message
    Glib::RefPtr<Gtk::Button> m_close;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Close button (hide about dialog)
    closeDialog m_closeDialog;
};
