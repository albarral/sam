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

void ComsManip::loop()
{
    bool bvalid = false;
    
    LOG4CXX_INFO(logger, "> ?");    
    oResponder.listen();

    int reqCommand = oResponder.getCommandID();
    
    if (reqCommand != Responder::UNRECOGNIZED_WORD)
    {
        bvalid = true;
        LOG4CXX_INFO(logger, oResponder.getRawCommand());      
        sendManipCommand(reqCommand);
    }
    else
    {
        int numCommand = 0;        
        LOG4CXX_INFO(logger, oResponder.getRawCommand());      

        if (oResponder.isNumericCommand(numCommand))
        {
            bvalid = true;
            sendManipCommandAngle(numCommand);
        }
    }
      
    if (!bvalid)
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
        case manipulation::Commands::eMOVER_USE2:
        case manipulation::Commands::eMOVER_USE3:
        case manipulation::Commands::eMOVER_USE4:
        {
            // sets the name of the active joint
            std::vector<std::string> listJointNames = pBus->getConfig().getListJointNames();
            int index = reqCommand - manipulation::Commands::eMOVER_USE1;
            activeJointName = listJointNames.at(index);
            LOG4CXX_INFO(logger, "active joint = " << activeJointName);
            break;
        }

        default:
            LOG4CXX_INFO(logger, "> nothing requested");
            break;
    }    
}


void ComsManip::sendManipCommandAngle(int angleCommand)
{
    float angle = angleCommand;
    pBus->getConnections().getConnectionsJoint(activeJointName).getCOAngle().request(angle);
    LOG4CXX_INFO(logger, "angle=" << angleCommand);
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