/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneArea.h"

namespace sam 
{
// complete constructor    
BoneArea::BoneArea(int ID, std::string area)
{
    this->ID = ID;
    this->area = area;
}

BoneArea::~BoneArea()
{    
}
}
