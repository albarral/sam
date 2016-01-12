#ifndef __SAM_HEAD_SOBUS_H
#define __SAM_HEAD_SOBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/sensorT.h"

namespace sam 
{
namespace head
{    
// Part of the bus involving sensor data    
class SOBus
{
    private:        
        // watcher module
        brooks::SensorT<int> SO_HEAD_PAN; 
        brooks::SensorT<int> SO_HEAD_TILT;         
        
    public:
        SOBus();
        // watcher module        
        brooks::SensorT<int>& getSO_HEAD_PAN(){return SO_HEAD_PAN;};        
        brooks::SensorT<int>& getSO_HEAD_TILT() {return SO_HEAD_TILT;};           
};

}
}    
#endif
