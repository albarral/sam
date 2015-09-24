/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ControlMsg.h"

namespace sam 
{
namespace network
{
// complete constructor    
ControlMsg::ControlMsg(int moduleID, int actionID, int detail, int priority, int processed)
{
    this->moduleID = moduleID;
    this->actionID = actionID;
    this->detail = detail;
    this->priority = priority;
    this->processed = processed;    
}

ControlMsg::~ControlMsg()
{
}

std::string ControlMsg::toString()
{
    return ("ControlMsg: moduleID=" + std::to_string(moduleID) +  
            ", actionID=" + std::to_string(actionID) +  
            ", detail=" + std::to_string(detail) + 
            ", priority=" + std::to_string(priority) + 
            ", processed=" + std::to_string(processed));
}

}
}