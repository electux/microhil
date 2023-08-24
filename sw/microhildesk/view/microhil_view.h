/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view.h
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

#include <vector>
#include <gtkmm/builder.h>
#include "home/microhil_view_home.h"
#include "dialog/microhil_view_dialog.h"
#include "settings/log/microhil_view_log.h"
#include "settings/serial/microhil_view_serial.h"
#include "about/microhil_view_about.h"
#include "microhil_view_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILView class declaration and definition 
class MicroHILView: public AbMicroHILView
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILView constructor
    MicroHILView();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILView destructor
    ~MicroHILView() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting home view
    /// @return Home view instance
    Glib::RefPtr<MicroHILViewHome> getHome();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log settings
    /// @return Log settings instance
    Glib::RefPtr<MicroHILViewLog> getLogSettings();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting serial settings
    /// @return Serial settings instance
    Glib::RefPtr<MicroHILViewSerial> getSerialSettings();

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Mapping views (signal and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing requests for triggering view
    /// @param id of requested view
    void onViewChanged(ViewId id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_builder{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Home view instance
    Glib::RefPtr<MicroHILViewHome> m_home{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dialog view instance
    Glib::RefPtr<MicroHILViewDialog> m_dialog{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log Settings view instance
    Glib::RefPtr<MicroHILViewLog> m_log{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial Settings view instance
    Glib::RefPtr<MicroHILViewSerial> m_serial{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief About view instance
    Glib::RefPtr<MicroHILViewAbout> m_about{nullptr};
};
