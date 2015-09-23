/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneComponent.h"

namespace sam 
{
namespace backbone 
{
const std::string BoneComponent::moduleType = "module";
const std::string BoneComponent::actionType = "action";
const std::string BoneComponent::sensorType = "sensor";

// complete constructor    
BoneComponent::BoneComponent(int ID, int type, std::string name, std::string desc)
{
    this->ID = ID;
    // set type string 
    switch (type)
    {
        case eTYPE_MODULE:
            this->type = moduleType;
            break;

        case eTYPE_ACTION:
            this->type = actionType;
            break;
            
        case eTYPE_SENSOR:
            this->type = sensorType;
            break;
            
        default:
            this->type = "";
            break;
    }
            
    this->name = name;
    this->description = desc;
}

BoneComponent::~BoneComponent()
{
}

}
}