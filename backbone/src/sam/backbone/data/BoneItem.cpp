/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "BoneItem.h"

namespace sam 
{
namespace backbone 
{
// complete constructor    
BoneItem::BoneItem(int ID, int type, std::string name, std::string desc)
{
    this->ID = ID;
    // set type string (action or sensor)
    if (type == eTYPE_ACTION)
        this->type = actionType;
    else if (type == eTYPE_SENSOR)
        this->type = sensorType;
    else
        this->type = "";
            
    this->name = name;
    this->description = desc;
}

BoneItem::~BoneItem()
{
}

}
}