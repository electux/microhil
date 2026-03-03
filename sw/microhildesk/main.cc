////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// main.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <application.h>

using namespace Electux::App;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief The main entry point of the microhildesk application.
///
/// This function initializes the entry application and starts the main
/// execution loop, returning the final exit status.
///
/// @param argc The number of command-line arguments.
/// @param argv The array of command-line arguments.
/// @return The exit status of the application (0 for success).
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	auto app = EntryApplication::create();
	const int status = app->run(argc, argv);

	return status;
}
