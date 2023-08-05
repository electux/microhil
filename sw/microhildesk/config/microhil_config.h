/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config.h
 * Copyright (C) 2021 Vladimir Roncevic <elektron.ronca@gmail.com>
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <glibmm.h>
#include <glibmm/keyfile.h>
#include "microhil_config_abstract.h"

class MicroHILConfig: public AbMicroHILConfig
{
    public:
        MicroHILConfig();
        ~MicroHILConfig() = default;

        bool load() final;
        bool validate() final;

        Glib::ustring getDevice() final;
        int getBaudRate() final;
        int getDataBits() final;
        Glib::ustring getParity() final;
        int getStopBits() final;

    private:
        bool checkConfigPath();

        std::string m_homePath{};
        std::string m_configFilePath{};
        Glib::KeyFile m_configuration{};
};
