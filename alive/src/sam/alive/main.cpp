/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM HEAD

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/alive/ConsoleControl.h"
#include "sam/head/HeadManager.h"
#include "sam/head/bus/Bus.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.alive"));

using namespace sam;

void testSam();

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testSam();
      
    return 0;
}


void testSam()
{        
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< SAM is ALIVE >>>>>>>>>>>>>>\n");
        
    head::HeadManager oHeadManager;    
    alive::ConsoleControl oConsoleControl;
 
    oHeadManager.startModules();
    oConsoleControl.init();

    head::Bus& oBus = oHeadManager.getBus();
        
    // wait for user commands
    while (!oConsoleControl.want2Quit())
    {
        oConsoleControl.fetchCommand();
        // command requested -> move head
        if (oConsoleControl.isCmdRequested())
        {
            // move head
            int pan = oConsoleControl.getPan();
            int tilt = oConsoleControl.getTilt();
            oBus.getCOBus().getCO_HEAD_PAN().request(pan);            
            oBus.getCOBus().getCO_HEAD_TILT().request(tilt);            
        }
    }
    
    oHeadManager.stopModules();
    sleep(2);
    
    LOG4CXX_INFO(logger, "End of test"); 
}
