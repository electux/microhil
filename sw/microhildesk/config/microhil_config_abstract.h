/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config_abstract.h
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

class AbMicroHILConfig
{
    public:
        AbMicroHILConfig() = default;
        ~AbMicroHILConfig() = default;

        virtual bool load() = 0;
        virtual bool validate() = 0;

        void setPreValid(bool configValid) {m_configPreValidate = configValid;}
        bool isPreValid() const {return m_configPreValidate;};

        virtual Glib::ustring getDevice() = 0;
        virtual int getBaudRate() = 0;
        virtual int getDataBits() = 0;
        virtual Glib::ustring getParity() = 0;
        virtual int getStopBits() = 0;

    private:
        bool m_configPreValidate{false};
};
