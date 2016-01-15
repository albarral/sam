#ifndef __SAM_HEAD_COBUS_H
#define __SAM_HEAD_COBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/controlT2.h"

namespace sam 
{
namespace head
{    
// Control part of the bus
class COBus
{
    private:                
        brooks::ControlT2<int> CO_HEAD_PAN; 
        brooks::ControlT2<int> CO_HEAD_TILT; 
        
    public:
        COBus();
        brooks::ControlT2<int>& getCO_HEAD_PAN() {return CO_HEAD_PAN;};           
        brooks::ControlT2<int>& getCO_HEAD_TILT() {return CO_HEAD_TILT;};           
};

}
}    
#endif
