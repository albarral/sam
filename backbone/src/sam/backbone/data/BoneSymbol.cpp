/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneSymbol.h"

namespace sam 
{
// complete constructor    
BoneSymbol::BoneSymbol(int ID, int area, int category, std::string symbol, std::string name)
{
    this->ID = ID;
    this->area = area;
    this->category =  category;
    this->symbol = symbol;
    this->name = name;
}

BoneSymbol::~BoneSymbol()
{
}
}
