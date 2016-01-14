#ifndef __SAM_LOOK_BUS_H
#define __SAM_LOOK_BUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "sam/look/bus/COBus.h"
#include "sam/look/bus/SOBus.h"


namespace sam 
{
namespace look
{    
// Bus for modules interconnection inside player app
class Bus
{
    private:        
        bool benabled;        
        COBus oCOBus;   // control data
        SOBus oSOBus;   // sensor data
                
    public:
        Bus();

        COBus& getCOBus() {return oCOBus;};
        SOBus& getSOBus() {return oSOBus;};
};

}
}    
#endif
