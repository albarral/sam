/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "SensorMsg.h"

namespace sam 
{
namespace network
{
// complete constructor    
SensorMsg::SensorMsg(int moduleID, int sensorID, int detail)
{
    this->moduleID = moduleID;
    this->sensorID = sensorID;
    this->detail = detail;
//    this->updates = updates;
}

SensorMsg::~SensorMsg()
{
}

std::string SensorMsg::toString()
{
    return ("SensorMsg: moduleID=" + std::to_string(moduleID) +  
            ", sensorID=" + std::to_string(sensorID) +  
            ", detail=" + std::to_string(detail));
//            + ", updates=" + std::to_string(updates));
}

}
}