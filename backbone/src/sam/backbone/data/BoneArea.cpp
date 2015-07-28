/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneArea.h"

namespace sam 
{
// complete constructor    
BoneArea::BoneArea(int area, std::string name)
{
    this->area = area;
    this->name = name;
}

BoneArea::~BoneArea()
{    
}
}
