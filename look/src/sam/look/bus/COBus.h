#ifndef __SAM_LOOK_COBUS_H
#define __SAM_LOOK_COBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/controlT.h"

namespace sam 
{
namespace look
{    
// Control part of the bus
class COBus
{
    private:                
//        brooks::ControlT<int> CO_HEAD_PAN; 
//        brooks::ControlT<int> CO_HEAD_TILT; 
        
    public:
        COBus();
//        brooks::ControlT<int>& getCO_HEAD_PAN() {return CO_HEAD_PAN;};           
//        brooks::ControlT<int>& getCO_HEAD_TILT() {return CO_HEAD_TILT;};           
};

}
}    
#endif
