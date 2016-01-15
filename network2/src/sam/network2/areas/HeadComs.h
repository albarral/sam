#ifndef __SAM_NETWORK_HEADCOMS_H
#define __SAM_NETWORK_HEADCOMS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/controlT2.h"
#include "sam/brooks/sensorT.h"

namespace sam 
{
namespace network
{    
// Network section for the Head area
class HeadComs
{
    private:                
        brooks::ControlT2<int> CO_HEAD_PAN;     // requested pan (degrees)
        brooks::ControlT2<int> CO_HEAD_TILT;     // requested tilt (degrees)
        brooks::SensorT<int> SO_HEAD_PAN;       // real pan (degrees)
        brooks::SensorT<int> SO_HEAD_TILT;       // real tilt (degrees)  
        brooks::SensorT<bool> SO_HEAD_PAN_LIMIT;       // pan limit reached
        brooks::SensorT<bool> SO_HEAD_TILT_LIMIT;       // tilt limit reached
        
    public:
        HeadComs();
        
        brooks::ControlT2<int>& getCO_HEAD_PAN() {return CO_HEAD_PAN;};           
        brooks::ControlT2<int>& getCO_HEAD_TILT() {return CO_HEAD_TILT;};           
        brooks::SensorT<int>& getSO_HEAD_PAN(){return SO_HEAD_PAN;};        
        brooks::SensorT<int>& getSO_HEAD_TILT() {return SO_HEAD_TILT;};           
        brooks::SensorT<bool>& getSO_HEAD_PAN_LIMIT() {return SO_HEAD_PAN_LIMIT;};
        brooks::SensorT<bool>& getSO_HEAD_TILT_LIMIT() {return SO_HEAD_TILT_LIMIT;};
};

}
}    
#endif
