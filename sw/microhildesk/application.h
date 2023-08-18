/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.h
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

#include <memory>
#include <gtkmm/application.h>
#include "model/microhil_model.h"
#include "view/microhil_view.h"
#include "controller/microhil_controller.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Application entry class declaration and definition
class Application
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Application constructor
    /// @param argc number of arguments
    /// @param argv array of arguments
    Application(int argc, char *argv[]);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application destructor
    ~Application() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Starts the application (run main loop)
    /// @return integer exit status (exit failure value is 1)
    int run();

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Application instance
    Glib::RefPtr<Gtk::Application> m_app{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Model instance
    std::shared_ptr<MicroHILModel> m_model{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief View instance
    std::shared_ptr<MicroHILView> m_view {nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Controller instance
    std::unique_ptr<MicroHILController> m_controller{nullptr};
};
