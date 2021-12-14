/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_desktop.h
 * Copyright (C) 2021 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * microhil_desktop is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * microhil_desktop is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MICROHIL_DEKSTOP_H
#define MICROHIL_DEKSTOP_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>

#define MICROHIL_TITLE "microHIL"
#define MICROHIL_VERSION "1.0.0"
#define MICROHIL_BORDER_WIDTH 10

class MicroHIL : public Gtk::Window
{
public:
  MicroHIL();
  ~MicroHIL();

protected:
  Gtk::Grid main_grid;
};

#endif
