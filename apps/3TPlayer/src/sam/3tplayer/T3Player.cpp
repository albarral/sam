/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "T3Player.h"

using namespace log4cxx;

namespace sam 
{
namespace t3player 
{
LoggerPtr T3Player::logger(Logger::getLogger("sam.t3player"));

// Constructor
T3Player::T3Player ()
{    
    LOG4CXX_INFO(logger, "");
    LOG4CXX_INFO(logger, "STARTING sam T3Player ...");
    
    oField = new Field(oBus);    

    // TEMP for TEST
    oVirBoard = new VirtualBoard();
    oField->setVirtualBoard(oVirBoard);        
}

// Destructor
T3Player::~T3Player ()
{        
    if (oField != NULL)
        delete (oField);
    
    if (oVirBoard != NULL)
        delete (oVirBoard);
}

void T3Player::startModules()
{
    LOG4CXX_INFO(logger, "FIELD module > launch");
    oField->launch();
}

void T3Player::stopModules()
{    
    //oField->stop();
    oField->stop();
    
    //oField->wait();
    //LOG4CXX_INFO(logger, "FOCUS thread > finished");            

    oField->wait();
    LOG4CXX_INFO(logger, "FIELD module > finished");            
}

}
}



