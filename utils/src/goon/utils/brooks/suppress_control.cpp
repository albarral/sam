/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "suppress_control.h"

namespace goon 
{
SuppressControl::SuppressControl ()
{    
    priority = 0;
}

void SuppressControl::request(int priority)
{  
    std::lock_guard<std::mutex> locker(mutex2);
    
    if (checkPriority(priority))
        Control::request();
}

bool SuppressControl::isRequested()
{
    std::lock_guard<std::mutex> locker(mutex2);
    
    clearPriority();    
    return Control::isRequested();
}

bool SuppressControl::checkPriority(int priority)
{
    if (priority > this->priority)
    {
        this->priority = priority;
        return true;
    }
    else
        return false;
}

void SuppressControl::clearPriority()
{
    priority = 0;
}
}


