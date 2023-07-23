/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_if.h
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

#ifndef MICROHIL_VIEW_IF_H
#define MICROHIL_VIEW_IF_H

#include <sigc++/sigc++.h>

class IMicroHILView
{
public:
    virtual ~IMicroHILView() = default;
    virtual void onChannel0() = 0;
    virtual void onChannel1() = 0;
    virtual void onChannel2() = 0;
    virtual void onChannel3() = 0;

    using channel0Changed = sigc::signal<void(bool)>;
    using channel1Changed = sigc::signal<void(bool)>;
    using channel2Changed = sigc::signal<void(bool)>;
    using channel3Changed = sigc::signal<void(bool)>;

    virtual channel0Changed channel0IsChanged() = 0;
    virtual channel1Changed channel1IsChanged() = 0;
    virtual channel2Changed channel2IsChanged() = 0;
    virtual channel3Changed channel3IsChanged() = 0;
};

#endif
