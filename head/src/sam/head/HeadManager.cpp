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

    oHeadController.init("IPCameraHead");
    oHeadController.connect(oBus);
    oHeadController.setFrequency(5.0);
    oHeadController.on();
}

void HeadManager::stopModules()
{
    LOG4CXX_INFO(logger, "HeadManager: stopping modules ..."); 

    oHeadController.off();
    oHeadController.wait();
        
    LOG4CXX_INFO(logger, "HeadManager: off");
}

}
}