/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_controller.h
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MICROHIL_CONTROLLER_H
#define MICROHIL_CONTROLLER_H

#include "microhil_model_if.h"
#include "microhil_view_if.h"
#include "microhil_controller_if.h"

class MicroHILController: public IMicroHILController
{
public:
    MicroHILController(IMicroHILModel *model, IMicroHILView *view);
    ~MicroHILController() = default;

    void setEnabled(bool switchController) final;
    bool isEnabled() const final;

private:

    bool enabled {false};
};

#endif
