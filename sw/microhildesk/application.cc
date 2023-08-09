/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.cc
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
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "application.h"

namespace
{
    constexpr char kAppId[]{"org.gtkmm.microhildesk"};
    constexpr char kHomeUI[]{"/org/gtkmm/microhildesk/home.ui"};
    constexpr char kwindowId[]{"Window"};
}

Application::Application(int argc, char *argv[])
{
    ////////////////////////////////////////////////////////////////////////
    // Setup app, builder
    m_app = Gtk::Application::create(argc, argv, kAppId);
    m_builder = Gtk::Builder::create_from_resource(kHomeUI);

    ////////////////////////////////////////////////////////////////////////
    // Check and prepare model, view and controller
    m_model = new MicroHILModel();
    m_builder->get_widget_derived(kwindowId, m_view);
    m_controller = new MicroHILController(m_model, m_view);
}

Application::~Application()
{
    if(m_model) delete m_model;
    if(m_view) delete m_view;
    if(m_controller) delete m_controller;
}

int Application::run()
{
    int status {EXIT_FAILURE};

    if(m_app && m_view)
    {
        status = m_app->run(*m_view);
    }

    return status;
}
