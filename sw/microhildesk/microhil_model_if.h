/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_model_if.h
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

#ifndef MICROHIL_MODEL_IF_H
#define MICROHIL_MODEL_IF_H

class IMicroHILModel
{
public:
    virtual ~IMicroHILModel() = default;
    virtual void setChannel0(bool channelState) = 0;
    virtual bool getChannel0() const = 0;
    virtual void setChannel1(bool channelState) = 0;
    virtual bool getChannel1() const = 0;
    virtual void setChannel2(bool channelState) = 0;
    virtual bool getChannel2() const = 0;
    virtual void setChannel3(bool channelState) = 0;
    virtual bool getChannel3() const = 0;
};

#endif
