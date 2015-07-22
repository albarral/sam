/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneMsg.h"

namespace sam 
{
// complete constructor    
BoneMsg::BoneMsg(int areaID, int moduleID, std::string message, int detail, int processed)
{
    this->areaID = areaID;
    this->moduleID = moduleID;
    this->info = message;
    this->detail = detail;
    this->processed = processed;    
}

BoneMsg::~BoneMsg()
{
}
}
