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
    /// @param argc is the number of arguments for the application
    /// @param argv is the array of arguments for the application
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
    MHRPtr<Gtk::Application> m_app{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Model instance
    MHSPtr<MicroHILModel> m_model{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief View instance
    MHSPtr<MicroHILView> m_view{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Controller instance
    MHUPtr<MicroHILController> m_controller{nullptr};
};
