/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/head/HeadManager.h"

namespace sam 
{
namespace head
{  
log4cxx::LoggerPtr HeadManager::logger(log4cxx::Logger::getLogger("sam.head"));

HeadManager::HeadManager() 
{
}

HeadManager::~HeadManager() 
{
}

void HeadManager::startModules()
{ 
    LOG4CXX_INFO(logger, "HeadManager: starting modules ..."); 
     
    if (isNetConnected())
    {
        oHeadController.init("IPCameraHead");
        // note: no internal bus, directly connected to the network
        oHeadController.netConnect(getNetConnection());
        oHeadController.setFrequency(5.0);
        oHeadController.on();
        LOG4CXX_INFO(logger, "HeadManager: started");  
    }
    // not connected to the network -> skip
    else
    {
        LOG4CXX_ERROR(logger, "HeadManager: not connected to network. Ignored!");  
    }
}

void HeadManager::stopModules()
{
    LOG4CXX_INFO(logger, "HeadManager: stopping modules ..."); 

    if (isNetConnected())
    {
        oHeadController.off();
        oHeadController.wait();        
        LOG4CXX_INFO(logger, "HeadManager: off");
    }
    // not connected to the network -> skip
    else
    {
        LOG4CXX_ERROR(logger, "HeadManager: not connected to network. Ignored!");  
    }
}

}
}