/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneModule.h"

namespace sam 
{
namespace backbone 
{
// complete constructor    
BoneModule::BoneModule(int ID, std::string name, std::string desc)
{
    this->ID = ID;
    this->name = name;
    this->description = desc;
}

BoneModule::~BoneModule()
{
}

}
}