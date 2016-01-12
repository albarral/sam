#ifndef __SAM_APP_PLAYER_H
#define __SAM_APP_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/head/bus/Bus.h"
#include "sam/head/modules/HeadController.h"

namespace sam 
{
namespace head
{  
class HeadManager
{
private:
    static log4cxx::LoggerPtr logger;
    Bus oBus;
    // modules
    HeadController oHeadController;
    
public:
    HeadManager();
    ~HeadManager();
        
    void startModules();
    void stopModules();
    
    Bus& getBus() {return oBus;};
};

}
}
#endif
