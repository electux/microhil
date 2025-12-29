/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.h
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
#pragma once

#include <gtkmm/application.h>
#include "view/home.h"
#include "view/settings/settings.h"
#include "view/help/help.h"
#include "view/about/about.h"

namespace Electux::App
{
    using AppHome = Electux::App::View::AppHome;
    using AppSettings = Electux::App::View::Settings::AppSettings;
    using AppHelp = Electux::App::View::Help::AppHelp;
    using AppAbout = Electux::App::View::About::AppAbout;

    //////////////////////////////////////////////////////////////////////////
    /// @brief Entry point for application definition
    class EntryApplication : public Gtk::Application
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief EntryApplication constructor
        explicit EntryApplication();

        //////////////////////////////////////////////////////////////////////
        /// @brief Creates reference pointer to EntryApplication
        static Glib::RefPtr<EntryApplication> create();

    protected:
        //////////////////////////////////////////////////////////////////////
        /// @brief Handler for the startup signal
        void on_startup() override;

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Maps signal/slots for application views
        void mapping();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action settings create window for application settings
        void onActionSettings();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action doc create window for help documentation
        void onActionDoc();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action about create dialog for about application
        void onActionAbout();

        //////////////////////////////////////////////////////////////////////
        /// @brief On action for quit
        void onActionQuit();

        //////////////////////////////////////////////////////////////////////
        /// @brief On handle close main window
        /// @return true if the signal has been handled
        bool onHandleClose();

        //////////////////////////////////////////////////////////////////////
        /// @brief Instances of application views
        ///   m_home - instance of AppHome (main window)
        ///   m_settings - instance of AppSettings (settings window)
        ///   m_help - instance of AppHelp (help window)
        ///   m_about - instance of AppAbout (about dialog)
        AppHome m_home{};
        AppSettings m_settings{};
        AppHelp m_help{};
        AppAbout m_about{};
    };
};

