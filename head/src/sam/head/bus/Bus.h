#ifndef __SAM_HEAD_BUS_H
#define __SAM_HEAD_BUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "sam/head/bus/COBus.h"
#include "sam/head/bus/SOBus.h"


namespace sam 
{
namespace head
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
