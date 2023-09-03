/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_log_abstract.h
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
#include "../../../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewLog class declaration and definition 
class AbMicroHILViewLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for log settings
    using SigLogSetup = sigc::signal<void(MHString, int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for log file path input
    using SigLogFilePath = sigc::signal<void(MHString)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for log level combobox
    using SigSelectLogLevel = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Cancel button (dismiss)
    using SigCancelLog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Ok button (confirm)
    using SigOkLog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewLog destructor
    virtual ~AbMicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log settings
    /// @return Signal for changed log settings
    virtual SigLogSetup logSetupChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log file path input
    /// @return Signal for changed log file path entry
    virtual SigLogFilePath logFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log file path input 
    virtual void onLogFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log level combobox
    /// @return Signal for selected log level combobox 
    virtual SigSelectLogLevel logLevelChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log level combobox
    virtual void onLogLevelChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    virtual SigCancelLog cancelLogTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button 
    /// @return Signal for clicked Ok button
    virtual SigOkLog okLogTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button
    virtual void onCancelLogTriggered() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button
    virtual void onOkLogTriggered() = 0;
};
