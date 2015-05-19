/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "module2.h"


namespace sam 
{
// Constructor
Module2::Module2 ()
{    
    state = Module2::state_OFF;
    period = 0;
}

void Module2::on()
{
    if (getState() == Module2::state_OFF)
    {
      t = std::thread(&Module2::run, this);              
    }           
}

void Module2::off()
{        
    setNextState(Module2::state_OFF);
}

void Module2::wait()
{
    t.join();
}

void Module2::setFrequency(float fps)
{
    std::lock_guard<std::mutex> locker(mutex);
    if (fps > 0.0)
        period = 1000000/fps;    // in microseconds
}

float Module2::getFrequency()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (period > 0)
        return (1000000/period);
    else
        return (0);        
}

void Module2::run ()
{
    // states begin unknown
    setState(Module2::state_UNKNOWN);
    forceNextState(Module2::state_UNKNOWN);
    init();
    while (!offRequested())
    {
        loop();
        usleep(period);
    }
    
    // final state OFF
    setState(Module2::state_OFF);
}

bool Module2::offRequested()
{
    return (getNextState() == Module2::state_OFF);        
}

int Module2::getState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state);        
}

void Module2::setState(int state)
{
    std::lock_guard<std::mutex> locker(mutex);
    this->state = state;    
}

int Module2::getNextState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (nextState);        
}

void Module2::setNextState(int state)
{
    std::lock_guard<std::mutex> locker(mutex);
    // if OFF is already set, the change is ignored
    if (this->nextState != Module2::state_OFF);                
        this->nextState = state;    
}

// restricted to be used just here
void Module2::forceNextState(int state) 
{
    std::lock_guard<std::mutex> locker(mutex);
    this->nextState = state;    
}

void Module2::updateState()
{
    std::lock_guard<std::mutex> locker(mutex);
    this->state = this->nextState;    
}


}


