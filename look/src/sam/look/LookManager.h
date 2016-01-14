#ifndef __SAM_LOOK_MANAGER_H
#define __SAM_LOOK_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/look/bus/Bus.h"
#include "sam/look/modules/tracker/Tracker.h"
#include "sam/network2/Network.h"

namespace sam 
{
namespace look
{  
class LookManager
{
private:
    static log4cxx::LoggerPtr logger;
    bool bconnected;        // connected to network
    Bus oBus;                  // internal bus     
    network::Network* pNetwork;     // sam's network
    // modules
    Tracker oTracker;
    
public:
    LookManager();
    ~LookManager();
               
    // network connection    
    void connect(network::Network& oNetwork);
    
    void startModules();
    void stopModules();
};

}
}
#endif
