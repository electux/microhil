/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_log.h
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

#include <iostream>
#include <fstream>
#include "microhil_log_abstract.h"

using namespace std;

class MicroHILLog: public AbMicroHILLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILLog constructor
    MicroHILLog();

    ////////////////////////////////////////////////////////////////////////
    // MicroHILLog destructor
    ~MicroHILLog();

    ////////////////////////////////////////////////////////////////////////
    // Setting file path for logger
    void setFilePath(const Glib::ustring logFilePath);

    ////////////////////////////////////////////////////////////////////////
    // Getting file path for logger
    Glib::ustring getFilePath() const;

    ////////////////////////////////////////////////////////////////////////
    // Open log file for collecting log messages
    bool open();

    ////////////////////////////////////////////////////////////////////////
    // Write log message
    void write(const Glib::ustring message, LogLevel level) final;

    ////////////////////////////////////////////////////////////////////////
    // Close log file
    bool close();

private:
    ////////////////////////////////////////////////////////////////////////
    // Getting current date and time
    Glib::ustring getCurrentDateTime() const;

    ////////////////////////////////////////////////////////////////////////
    // Convert log level type to human readable string 
    Glib::ustring getLogType(LogLevel level) const;

    Glib::ustring m_logFilePath{};
    ofstream m_logFile{};
    bool m_fileOpened {};
};
