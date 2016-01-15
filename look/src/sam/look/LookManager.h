#ifndef __SAM_LOOK_MANAGER_H
#define __SAM_LOOK_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/look/bus/Bus.h"
#include "sam/look/modules/tracker/Tracker.h"
#include "sam/network2/NetworkUser.h"

namespace sam 
{
namespace look
{  
// Manager of look modules.
// Derives from: NetworkUser    
class LookManager : public network::NetworkUser
{
private:
    static log4cxx::LoggerPtr logger;
    Bus oBus;                  // internal bus     
    // modules
    Tracker oTracker;
    
public:
    LookManager();
    ~LookManager();
                   
    void startModules();
    void stopModules();
};

}
}
#endif
