/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_model.h
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

#ifndef MICROHIL_MODEL_H
#define MICROHIL_MODEL_H

#include "microhil_model_if.h"

class MicroHILModel: public IMicroHILModel
{
public:
    MicroHILModel() = default;
    ~MicroHILModel() = default;

    void setChannel0(bool channelState) final;
    void setChannel1(bool channelState) final;
    void setChannel2(bool channelState) final;
    void setChannel3(bool channelState) final;

private:
    bool channel0 {false};
    bool channel1 {false};
    bool channel2 {false};
    bool channel3 {false};
};

#endif
