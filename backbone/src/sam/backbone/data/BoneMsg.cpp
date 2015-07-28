/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneMsg.h"

namespace sam 
{
// complete constructor    
BoneMsg::BoneMsg(int area, int module, int info, int detail, int processed)
{
    this->area = area;
    this->module = module;
    this->info = info;
    this->detail = detail;
    this->processed = processed;    
}

BoneMsg::~BoneMsg()
{
}

std::string BoneMsg::toString()
{
    return ("BoneMsg: area=" + std::to_string(area) + 
            ", module=" + std::to_string(module) +  
            ", info=" + std::to_string(info) +  
            ", detail=" + std::to_string(detail));                  
}
}
