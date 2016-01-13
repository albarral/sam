#ifndef __SAM_NETWORK_NETWORK_H
#define __SAM_NETWORK_NETWORK_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/controlT.h"
#include "sam/brooks/sensorT.h"

namespace sam 
{
namespace network
{    
// Network for interconnection of SAM areas
class Network
{
    private:                
        // Head section
        brooks::ControlT<int> CO_HEAD_PAN; 
        brooks::ControlT<int> CO_HEAD_TILT; 
        brooks::SensorT<int> SO_HEAD_PAN; 
        brooks::SensorT<int> SO_HEAD_TILT;         

    public:
        Network();

        // Head section
        brooks::ControlT<int>& getCO_HEAD_PAN() {return CO_HEAD_PAN;};           
        brooks::ControlT<int>& getCO_HEAD_TILT() {return CO_HEAD_TILT;};           
        brooks::SensorT<int>& getSO_HEAD_PAN(){return SO_HEAD_PAN;};        
        brooks::SensorT<int>& getSO_HEAD_TILT() {return SO_HEAD_TILT;};           
};

}
}    
#endif
