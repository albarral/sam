/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "log4cxx/ndc.h"

#include "Field.h"

using namespace std;
using namespace log4cxx;

namespace sam 
{
namespace t3player 
{
LoggerPtr Field::logger(Logger::getLogger("sam.t3player.field"));

// Constructor
Field::Field (Bus& oBus) : 
                mConfig(oBus.getConfig()), mConnections(oBus.getConnections()), mData(oBus.getData())
{
    Module::setState(eFIELD_OFF);
}

// Destructor
Field::~Field ()
{
}

void Field::run ()
{    
    LOG4CXX_INFO(logger, "FIELD module > on");      
    Module::setActive(true);      
    Module::setState(eFIELD_STATIC);

    while (!Module::stopRequested())
    {
        loop();           
        usleep(loop_ms);
    }

    Module::setState(eFIELD_OFF);
    Module::setActive(false);
    LOG4CXX_INFO(logger, "FIELD module > off");
}

void Field::loop ()
{    
    switch (getState())
    {            
        case eFIELD_STATIC:
            // waits till board changes, then jums to CHANGING

            if (checkBoardChanged())
            {
                changeState(eFIELD_CHANGING); 
            }
            break;
            
        case eFIELD_CHANGING:
            // waits till changes finished, then raises board changed flag & jums to CHANGED
            
            if (!checkBoardChanged())
            {
                mConnections.getSOBoardChanged().setValue(true);
                changeState(eFIELD_CHANGED);
            }
            break;
                    
        case eFIELD_CHANGED:
            // waits till ack is received, then lowers board changed flag & jumps to STATIC
            // if new changes happen, goes back to CHANGING

            if (checkBoardChanged())
            {
                changeState(eFIELD_CHANGING); 
            }
            // ack received -> STATIC & lower "board changed" flag
            else if (mConnections.getCOAckBoardChanged().isRequested())                
            {
                mConnections.getSOBoardChanged().setValue(false);
                changeState(eFIELD_STATIC); 
            }
            break;
    }   // end switch    
    
    Module::loop();
}

bool Field::checkBoardChanged()
{
    if (mConfig.isVirtualMode())
    {
        LOG4CXX_INFO(logger, "checkBoardChanged (virtual): ...");
        
        // TO DO ...
        // check table in DB that holds the state of the real board
                
        cv::Mat maskBoard = mVirBoard->getMatrix();
        
        Board& oBoard = mData.getBoard();
        oBoard.update(maskBoard);        
        
        if (oBoard.isChanged())
            return true;
        else 
            return false;
    }
    else
    {
        LOG4CXX_INFO(logger, "checkBoardChanged (real): to do ...");
        
        // TO DO ...
        // detect real changes on physical board
        
        return true;
    }    
}

void Field::stop()
{
    LOG4CXX_INFO(logger, "FIELD module > stop requested");
    Module::stop();
}

void Field::changeState(int nextState)
{
    Module::setState(nextState);
    
    log4cxx::NDC::pop();	
    switch (state) 
    {
        case eFIELD_OFF:            
            goSlow();
            LOG4CXX_INFO(logger, ">> off");
            log4cxx::NDC::push("off");   	
            break;
        case eFIELD_STATIC:
            goSlow();
            LOG4CXX_INFO(logger, ">> static");
            log4cxx::NDC::push("static");   	
            break;
        case eFIELD_CHANGING:
            goFast();
            LOG4CXX_INFO(logger, ">> changing");
            log4cxx::NDC::push("changing");   	
            break;
        case eFIELD_CHANGED:
            goFast();
            LOG4CXX_INFO(logger, ">> changed");
            log4cxx::NDC::push("changed");   	
            break;
    }               
}

void Field::goFast()
{
    loop_ms = mConfig.getFastLoopTime();
}

void Field::goSlow()
{
    loop_ms = mConfig.getSlowLoopTime();
}

}
}


