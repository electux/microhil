/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_dialog.cc
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
#include "microhil_view_dialog.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Dialog message id
    constexpr const char kDialogMessage[]{"DialogMessageText"};

    ////////////////////////////////////////////////////////////////////////
    /// Close button id for dialog message
    constexpr const char kCloseButtonId[]{"CloseDialog"};

    ////////////////////////////////////////////////////////////////////////
    /// String representation of info message type
    constexpr const char kInfoMessage[]{" INFO "};

    ////////////////////////////////////////////////////////////////////////
    /// String representation of warning message type
    constexpr const char kWarningMessage[]{" WARNING "};

    ////////////////////////////////////////////////////////////////////////
    /// String representation of error message type
    constexpr const char kErrorMessage[]{" ERROR "};
} // namespace

MHViewDialog::MHViewDialog(BaseObjectType *object, RPtr<Gtk::Builder> const &ui)
    : Gtk::Dialog(object)
    , m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    /// Binds Dialog message
    m_text = RPtr<Gtk::Label>::cast_dynamic(m_ui->get_object(kDialogMessage));

    ////////////////////////////////////////////////////////////////////////
    /// Binds Close button
    m_close = RPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kCloseButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Maps Close button (signal and slot)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Hides Dialog by default
    this->hide();
}

void MHViewDialog::setMessage(const UString &message, const MessageType type)
{
    const auto messageType = toUnicodeStringMessageType(type);
    this->set_title(messageType);
    m_text->set_text(message);
}

UString MHViewDialog::toUnicodeStringMessageType(const MessageType type)
{
    switch (type)
    {
    case MessageType::MICROHIL_INFO:
        return kInfoMessage;
    case MessageType::MICROHIL_WARNING:
        return kWarningMessage;
    case MessageType::MICROHIL_ERROR:
        return kErrorMessage;
    }

    return kInfoMessage;
}
