/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * application.cc
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
#include "application.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// MicroHIL application ID
    constexpr const char kAppId[]{"org.electux.microhildesk"};
} // namespace

Application::Application(int argc, char *argv[])
    : m_app{Gtk::Application::create(argc, argv, kAppId)}
    , m_model{makeSPtr<MHModel>()}
    , m_view{makeSPtr<MHView>()}
    , m_controller{makeSPtr<MHController>(m_model, m_view)}
{
}

int Application::run()
{
    auto status{EXIT_FAILURE};

    if (m_app && m_view)
    {
        ////////////////////////////////////////////////////////////////////
        /// Starts the MicroHIL application
        status = m_app->run(*(m_view->getHome().get()));
    }

    return status;
}
