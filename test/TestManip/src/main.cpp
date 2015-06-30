/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM MANIPULATION

#include <vector>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/manipulation/ArmManager.h"

void testManipulation();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.manipulation"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testManipulation();
      
    return 0;
}

void testManipulation()
{
    LOG4CXX_INFO(logger, "<<<<<<<<<<<<<<<< TEST MANIPULATION >>>>>>>>>>>>>>");      
    
    std::vector<float> listPrevAngles;
    
    sam::ArmManager oArmManager;    
    oArmManager.startModules();
    
    while (!oArmManager.checkEndRequested()) 
    {
        oArmManager.readSollAngles();
        std::vector<float>& listSollAngles = oArmManager.getSollAngles();
        
        if (listSollAngles != listPrevAngles)
        {
            LOG4CXX_INFO(logger,"moved angles: " << listSollAngles.at(0) << ", " << listSollAngles.at(1) << ", " << listSollAngles.at(2));      
            listPrevAngles = listSollAngles;            
        }

        sleep(1);
    }    
    
    oArmManager.stopModules();

    return;
}

