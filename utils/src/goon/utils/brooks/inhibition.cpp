/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "inhibition.h"

namespace goon 
{
// Constructor
Inhibition::Inhibition ()
{    
    loops = 0;
}

void Inhibition::request(int loops)
{
    std::lock_guard<std::mutex> locker(mutex);
    if (loops > this->loops)
        this->loops = loops;
}

bool Inhibition::isRequested()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (loops > 0)
    {
        loops--;
        return true;
    }
    else         
        return false;
}
}


