/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "control.h"

namespace goon 
{
// Constructor
Control::Control ()
{    
    brequested = false;
}

void Control::request()
{
    std::lock_guard<std::mutex> locker(mutex1);
    brequested = true;
}

bool Control::checkRequested()
{
    std::lock_guard<std::mutex> locker(mutex1);
    if (brequested)
    {
        brequested = false;
        return true;
    }
    else
        return false;
}
}


