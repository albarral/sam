/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM HEAD

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/head/HeadManager.h"
#include "sam/head/bus/Bus.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.head"));

using namespace sam;

void testHead();

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testHead();
      
    return 0;
}

void testHead()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST HEAD  >>>>>>>>>>>>>>\n");
    
    int pan, tilt;
    std::vector<int> listPans;  // LIFO list
    listPans.push_back(10);
//    listPans.push_back(30);
//    listPans.push_back(20);
//    listPans.push_back(10);
    std::vector<int> listTilts; // LIFO list
    listTilts.push_back(30);
    listTilts.push_back(20);
    listTilts.push_back(10);
    
    head::HeadManager oHeadManager;    
    head::Bus& oBus = oHeadManager.getBus();

    oHeadManager.startModules();

    LOG4CXX_INFO(logger, "front request");
    pan = tilt = 0;
    oBus.getCOBus().getCO_HEAD_PAN().request(pan);            
    oBus.getCOBus().getCO_HEAD_TILT().request(tilt);            
    sleep(3);
    
    while (!listTilts.empty()) 
    {
        // there are pans to test
        if (!listPans.empty())
        {
            pan = listPans.back();
            listPans.pop_back();
            LOG4CXX_INFO(logger, "pan request " << pan);
            oBus.getCOBus().getCO_HEAD_PAN().request(pan);            
        }        
        // there are pans to test
        else if (!listTilts.empty())
        {
            tilt = listTilts.back();
            listTilts.pop_back();
            LOG4CXX_INFO(logger, "tilt request " << tilt);
            oBus.getCOBus().getCO_HEAD_TILT().request(tilt);            
        }

        sleep(3);
    }    
    
    oHeadManager.stopModules();

    return;
}
