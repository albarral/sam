/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "NetworkCode.h"

namespace sam 
{
namespace network
{
const std::string NetworkCode::typeModule = "module";
const std::string NetworkCode::typeAction = "action";
const std::string NetworkCode::typeSensor = "sensor";

// complete constructor    
NetworkCode::NetworkCode(int ID, int type, std::string name)
{
    this->ID = ID;
    // set type string 
    switch (type)
    {
        case eTYPE_MODULE:
            this->type = typeModule;
            break;

        case eTYPE_ACTION:
            this->type = typeAction;
            break;
            
        case eTYPE_SENSOR:
            this->type = typeSensor;
            break;
            
        default:
            this->type = "";
            break;
    }
            
    this->name = name;
}

NetworkCode::~NetworkCode()
{
}

}
}