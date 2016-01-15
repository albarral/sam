/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/look/LookManager.h"

namespace sam 
{
namespace look
{  
log4cxx::LoggerPtr LookManager::logger(log4cxx::Logger::getLogger("sam.look"));

LookManager::LookManager() 
{
}

LookManager::~LookManager() 
{
}

void LookManager::startModules()
{ 
    LOG4CXX_INFO(logger, "LookManager: starting modules ..."); 

    // start modules if connected to the network
    if (isNetConnected())
    {
        oTracker.init();
        oTracker.busConnect(oBus);
        oTracker.netConnect(getNetConnection());
        oTracker.setFrequency(5.0);
        oTracker.on();
        LOG4CXX_INFO(logger, "LookManager: started");  
    }
    // not connected to the network -> skip
    else
    {
        LOG4CXX_ERROR(logger, "LookManager: not connected to network. Ignored!");  
    }
}

void LookManager::stopModules()
{
    LOG4CXX_INFO(logger, "LookManager: stopping modules ..."); 

    if (isNetConnected())
    {    
        oTracker.off();
        oTracker.wait();
        LOG4CXX_INFO(logger, "LookManager: off");
    }
    // not connected to the network -> skip
    else
    {
        LOG4CXX_ERROR(logger, "LookManager: not connected to network. Ignored!");  
    }        
}

}
}