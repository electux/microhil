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

class MicroHILViewDialog: public AbMicroHILViewDialog, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewDialog constructor
    MicroHILViewDialog(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewDialog destructor
    ~MicroHILViewDialog() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from dialog Close button
    closeDialog closeDialogChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing Close button for dialog
    void onCloseDialogChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Show dialog with message
    void show(const Glib::ustring message, MessageType type) final;

    ////////////////////////////////////////////////////////////////////////
    // Hide dialog
    void hide() final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Conversion of message type to unicode string
    Glib::ustring toUnicodeStringMessageType(MessageType type) const;

    ////////////////////////////////////////////////////////////////////////
    // Map Close button signal and slot
    void mapping();

    Glib::RefPtr<Gtk::Builder> m_ui;
    Glib::RefPtr<Gtk::Label> m_text;
    Glib::RefPtr<Gtk::Button> m_close;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Close button (hide about dialog)
    closeDialog m_closeDialog;
};
