/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_log.cc
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
#include "microhil_view_log.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Entry id
    constexpr const char kLogDevicePathId[]{"LogFilePathInput"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Combobox id
    constexpr const char kLogLevelSelectorId[]{"LogLevelSelector"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Cancel button id
    constexpr const char kCancelButtonId[]{"LogCancel"};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Ok button id
    constexpr const char kOkButtonId[]{"LogOk"};
} // namespace

MHViewLog::MHViewLog(BaseObjectType *object, RPtr<Gtk::Builder> const &ui)
    : Gtk::Dialog(object)
    , m_ui{ui}
{
    ////////////////////////////////////////////////////////////////////////
    /// Binds Log file path entry
    m_device =
        RPtr<Gtk::Entry>::cast_dynamic(m_ui->get_object(kLogDevicePathId));

    ////////////////////////////////////////////////////////////////////////
    /// Binds Log level combobox
    m_level = RPtr<Gtk::ComboBoxText>::cast_dynamic(
        m_ui->get_object(kLogLevelSelectorId)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Binds Cancel button
    m_cancel =
        RPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kCancelButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Binds Ok button
    m_ok = RPtr<Gtk::Button>::cast_dynamic(m_ui->get_object(kOkButtonId));

    ////////////////////////////////////////////////////////////////////////
    /// Maps all widgets (signals and slots)
    mapping();

    ////////////////////////////////////////////////////////////////////////
    /// Hides Log Settings by default
    this->hide();
}

void MHViewLog::logSettingsLoaded(UString &filePath, int logLevel)
{
    m_device->set_text(filePath);
    m_level->set_active(logLevel);
}
