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

#include <gtkmm/builder.h>
#include "dialog/microhil_view_dialog.h"
#include "about/microhil_view_about.h"
#include "microhil_iview.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHView class is implementation of view
class MHView : public IMHView
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHView constructor
    MHView();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHView destructor
    inline ~MHView() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for controling serial port
    /// @return Signal for clicked Connect/Disconnect
    SigSerialControl serialControlChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets home view
    /// @return Home view instance
    MHRPtr<MHViewHome> getHome() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log settings view
    /// @return Log view settings instance
    MHRPtr<MHViewLog> getLogSettings() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets serial settings view
    /// @return Serial view settings instance
    MHRPtr<MHViewSerial> getSerialSettings() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps views (signal and slots)
    void mapping() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing requests for triggering view
    /// @param id represents id of requested view
    void onViewChanged(ViewId id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok request for serial port changes
    /// @param state true for confirm operation, else false
    void onConfirmSerialSettings(bool state) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    MHRPtr<Gtk::Builder> m_builder{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Connect/Disconnect the serial port
    SigSerialControl m_serialPortChanged{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Home view instance
    MHRPtr<MHViewHome> m_home{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Dialog view instance
    MHRPtr<MHViewDialog> m_dialog{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log Settings view instance
    MHRPtr<MHViewLog> m_log{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Serial Settings view instance
    MHRPtr<MHViewSerial> m_serial{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief About view instance
    MHRPtr<MHViewAbout> m_about{nullptr};
};
