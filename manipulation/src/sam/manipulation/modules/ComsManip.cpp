/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
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
    std::vector<std::string>& listCommands = oCommands.getListCommands();
    for (int i=0; i<listCommands.size(); i++)
    {
        oResponder.addWord(listCommands.at(i));
    }

    activeJointName = "shoulderH";
    benabled = true;    
    LOG4CXX_INFO(logger, "ComsManip initialized");          
};

void ComsManip::connect(manipulation::Bus& oBus)
{
    pBus = &oBus;
    bconnected = true;

    LOG4CXX_INFO(logger, "ComsManip connected to bus");      
}

void ComsManip::first()
{    
    log4cxx::NDC::push("coms");   	
    showResponderWords();
}

void ComsManip::loop ()
{
    LOG4CXX_INFO(logger, "> ?");    
    oResponder.listen();

    int reqCommand = oResponder.getCommandID();
    
    if (reqCommand != Responder::INVALID_WORD)
    {
        LOG4CXX_INFO(logger, oResponder.getCommandString());      
        sendManipCommand(reqCommand);
    }
    else
        LOG4CXX_ERROR(logger, "Invalid command!");
}


void ComsManip::sendManipCommand(int reqCommand)
{
    switch (reqCommand)
    {        
        case manipulation::Commands::eMOVER_RIGHT:
        case manipulation::Commands::eMOVER_LEFT:
        case manipulation::Commands::eMOVER_BRAKE:
        case manipulation::Commands::eMOVER_KEEP:
        case manipulation::Commands::eMOVER_STOP:            
            pBus->getConnections().getConnectionsJoint(activeJointName).getCOAction().request(reqCommand);            
            break;
 
        case manipulation::Commands::eMOVER_USE1:
            activeJointName = "shoulderH";
            LOG4CXX_INFO(logger, "active joint = " << activeJointName);
            break;

        case manipulation::Commands::eMOVER_USE2:
            activeJointName = "shoulderV";
            LOG4CXX_INFO(logger, "active joint = " << activeJointName);
            break;

        case manipulation::Commands::eMOVER_USE3:
            activeJointName = "elbow";
            LOG4CXX_INFO(logger, "active joint = " << activeJointName);
            break;

        default:
            LOG4CXX_INFO(logger, "> nothing requested");
            break;
    }    
}

void ComsManip::showResponderWords()
{    
    LOG4CXX_INFO(logger, "List of accepted words:");      
    std::vector<std::string>& listWords = oResponder.getListWords();
    std::vector<std::string>::iterator it_word = listWords.begin();

    while (it_word != listWords.end())
    {
        LOG4CXX_INFO(logger, *it_word);             
        it_word++;
    }
}

}