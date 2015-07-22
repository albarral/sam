/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneModul.h"

namespace sam 
{
// complete constructor    
BoneModul::BoneModul(int areaID, int moduleID, std::string module)
{
    this->areaID = areaID;
    this->moduleID = moduleID;
    this->module = module;
}

BoneModul::~BoneModul()
{
}
}
