/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM MANIPULATION

#include <unistd.h> // for sleep() 
#include <log4cxx/xml/domconfigurator.h>

#include "sam/manipulation/ArmManager.h"

void testManipulation();

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testManipulation();
      
    return 0;
}

void testManipulation()
{
    sam::ArmManager oArmManager;
    
    oArmManager.startModules();
    
    sleep(20);
    
    oArmManager.stopModules();

    return;
}

