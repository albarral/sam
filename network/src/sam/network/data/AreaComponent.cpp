/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "AreaComponent.h"

namespace sam 
{
namespace network
{
const std::string AreaComponent::moduleType = "module";
const std::string AreaComponent::actionType = "action";
const std::string AreaComponent::sensorType = "sensor";

// complete constructor    
AreaComponent::AreaComponent(int ID, int type, std::string name)
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
    //this->description = desc;
}

AreaComponent::~AreaComponent()
{
}

}
}