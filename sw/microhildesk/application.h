/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.h
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
#pragma once

#include <gtkmm/application.h>
#include "model/microhil_model.h"
#include "view/microhil_view.h"
#include "controller/microhil_controller.h"

class Application
{
public:
    ////////////////////////////////////////////////////////////////////////
    // Application constructor
    Application(int argc, char *argv[]);

    ////////////////////////////////////////////////////////////////////////
    // Application destructor
    ~Application();

    ////////////////////////////////////////////////////////////////////////
    // Starts the application (run main loop)
    int run();

private:
    Glib::RefPtr<Gtk::Application> m_app;
    Glib::RefPtr<Gtk::Builder> m_builder;

    MicroHILModel *m_model{nullptr};
    MicroHILView *m_view {nullptr};
    MicroHILController *m_controller{nullptr};
};
