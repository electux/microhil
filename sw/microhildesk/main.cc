/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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
#include "microhil_model.h"
#include "microhil_view.h"
#include "microhil_controller.h"
#include <gtkmm/application.h>

namespace
{
    constexpr char kAppId[]{"org.gtkmm.microhildesk"};
    constexpr char kHomeUI[]{"/org/gtkmm/microhildesk/home.ui"};
    constexpr char kwindowId[]{"Window"};
}

int main(int argc, char *argv[])
{
    MicroHILModel *model = new MicroHILModel();

    MicroHILView *view {nullptr};
    auto app = Gtk::Application::create(argc, argv, kAppId);
    auto builder = Gtk::Builder::create_from_resource(kHomeUI);
    builder->get_widget_derived(kwindowId, view);

    MicroHILController *controller = new MicroHILController();

    auto result = app->run(*view);

    delete model;
    delete view;
    delete controller;

    return result;
}
