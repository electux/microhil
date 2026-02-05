/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * log.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <log/log.h>

using namespace Electux::App::Logger;

Log::~Log()
{
    close();
}

void Log::setLevel(LogLevel level)
{
    m_level = level;
}

Log::LogLevel Log::getLevel() const
{
    return m_level;
}

void Log::setOutputFile(const std::string &output)
{
    m_outputFile = output;
}

bool Log::open()
{
    std::lock_guard<std::mutex> lk(m_mutex);

    if (m_outputFile.empty())
    {
        return false;
    }

    m_stream.open(m_outputFile, std::ios::out | std::ios::app);
    return m_stream.is_open();
}

bool Log::close()
{
    std::lock_guard<std::mutex> lk(m_mutex);

    if (m_stream.is_open())
    {
        m_stream.close();
        return true;
    }

    return false;
}

void Log::log(const std::string &message, LogLevel level)
{
    std::lock_guard<std::mutex> lk(m_mutex);

    if (!m_stream.is_open())
    {
        return;
    }

    if (static_cast<int>(level) > static_cast<int>(m_level))
    {
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_r(&t, &tm);

    m_stream << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S") << " ";

    switch (level)
    {
    case LogLevel::Error:
        m_stream << "[ERROR] ";
        break;
    case LogLevel::Warning:
        m_stream << "[WARN] ";
        break;
    case LogLevel::Info:
        m_stream << "[INFO] ";
        break;
    }

    m_stream << message << std::endl;
    m_stream.flush();
}
