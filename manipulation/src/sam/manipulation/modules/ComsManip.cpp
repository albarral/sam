/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "log4cxx/ndc.h"
#include "ComsManip.h"
#include "sam/manipulation/bus/Bus.h"
#include "sam/manipulation/modules/Commands.h"

using namespace log4cxx;

namespace sam
{
LoggerPtr ComsManip::logger(Logger::getLogger("sam.manipulation"));

// Constructor 
ComsManip::ComsManip ()
{    
       benabled = false;
 }


// Destructor
ComsManip::~ComsManip ()
{
}

void ComsManip::init ()
{
    // build command list
    // important:same order as in eCommands enum
    oResponder.addWord("mover");
    oResponder.addWord("movel");
    oResponder.addWord("brake");
    oResponder.addWord("keep");
    oResponder.addWord("stop");

    benabled = true;    
    LOG4CXX_INFO(logger, "ComsManip initialized");          
};

void ComsManip::connect(manipulation::Bus& oBus)
{
    mBus = &oBus;
    bconnected = true;

    LOG4CXX_INFO(logger, "ComsManip connected to bus");      
}

void ComsManip::first()
{    
    oResponder.showAcceptedWords();
}

void ComsManip::loop ()
{
    oResponder.listen();

    int reqCommand = oResponder.getRequestedCommand();
    
    if (reqCommand != Responder::INVALID_WORD)
    {
        sendManipCommand(reqCommand);
    }
    else
        LOG4CXX_ERROR(logger, "Invalid command!");
}


void ComsManip::sendManipCommand(int reqCommand)
{
    LOG4CXX_INFO(logger, "ok");      
    switch (reqCommand)
    {
        case manipulation::Commands::eMOVER_MOVE_R:
        case manipulation::Commands::eMOVER_MOVE_L:
        case manipulation::Commands::eMOVER_BRAKE:
        case manipulation::Commands::eMOVER_KEEP:
        case manipulation::Commands::eMOVER_STOP:
            
            mBus->getConnections().getShoulderConnectionsH().getCOAction().request(reqCommand);
            break;
 
        default:
            LOG4CXX_INFO(logger, "> nothing requested");
            break;
    }    
}

}