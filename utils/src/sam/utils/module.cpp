/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "module.h"

using namespace std;

namespace goon 
{
// Constructor
Module::Module ()
{    
    bactive = false;
    tics = 0;
}

void Module::launch()
{
    if (!isActive())
    {
      setActive (true);
      bstop = false;
      t = std::thread(&Module::run, this);              
    }           
}

void Module::stop()
{        
    std::lock_guard<std::mutex> locker(mutex);
    bstop = true;    
}

void Module::wait()
{
    t.join();
}

//void Module::run ()
//{  
//    setActive(true);      
//    while (!stopRequested())
//    {
//        loop();
//        sleep(period);
//    }
//    setActive(false);
//}

void Module::loop()
{
    // no lock needed, modules connected by Brooks sensors
    //std::lock_guard<std::mutex> locker(mutex);
    tics++;
}

bool Module::stopRequested()
{
    std::lock_guard<std::mutex> locker(mutex);
    return bstop;        
}

void Module::setActive(bool bvalue)
{
    std::lock_guard<std::mutex> locker(mutex);
    this->bactive = bvalue;    
}

bool Module::isActive()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (bactive);        
}

void Module::setState(int state)
{
    // no lock needed, modules connected by Brooks sensors
    //std::lock_guard<std::mutex> locker(mutex);
    prevState = this->state;
    this->state = state;    
}

int Module::getState()
{
    // no lock needed, modules connected by Brooks sensors
    //std::lock_guard<std::mutex> locker(mutex);
    return (state);        
}

int Module::getPrevState()
{
    // no lock needed, modules connected by Brooks sensors
    //std::lock_guard<std::mutex> locker(mutex);
    return (prevState);        
}

int Module::getTics()
{
    // no lock needed, modules connected by Brooks sensors
    //std::lock_guard<std::mutex> locker(mutex);
    return (tics);        
}


}


