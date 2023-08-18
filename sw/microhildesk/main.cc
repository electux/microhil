/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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

////////////////////////////////////////////////////////////////////////
/// @brief Create application
/// @param argc number of arguments
/// @param argv array of arguments
/// @return std::unique_ptr for application
std::unique_ptr<Application> create(int argc, char *argv[]);

////////////////////////////////////////////////////////////////////////
/// @brief Main entry point
/// @param argc number of arguments
/// @param argv array of arguments
/// @return integer exit status (exit failure value is 1)
int main(int argc, char *argv[])
{
    auto app = create(argc, argv);
    int status {EXIT_FAILURE};

    if(app)
    {
        status = app->run();
    }

    return status;
}

std::unique_ptr<Application> create(int argc, char *argv[])
{
    return make_unique<Application>(argc, argv);
}
