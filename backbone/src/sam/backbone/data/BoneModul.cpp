/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneModul.h"

namespace sam 
{
// complete constructor    
BoneModul::BoneModul(int area, int module, std::string symbol)
{
    this->area = area;
    this->module = module;
    this->symbol = symbol;
}

BoneModul::~BoneModul()
{
}
}
