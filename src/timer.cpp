/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#include "timer.h"

#include <cmath>

Timer::Timer()
    : sec_(0)
{
}

void Timer::start()
{
    sec_ = std::lround(ofGetElapsedTimef());
}

void Timer::stop()
{
    sec_ = 0;
}

string Timer::current() const
{
    int t = currentSec();
    int s = t % 60;
    int m = t / 60;
    int h = t / 3600;

    char buf[20];
    sprintf(buf, "%0d:%02d:%02d", h, m, s);
    return buf;
}

int Timer::currentSec() const
{
    return std::lround(ofGetElapsedTimef()) - sec_;
}
