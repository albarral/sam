/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cppconn/resultset.h>

#include "AreaConnection.h"
#include "sam/backbone/config/Config.h"
#include "utils2/DBClient.h"

namespace sam 
{
namespace backbone 
{
AreaConnection::AreaConnection() 
{
    btuned = false;
}

void AreaConnection::tune2Table(std::string tabName)
{
    this->tabComponents = tabName;

    // query for selecting area modules
    selectModules = "SELECT * FROM " + tabComponents 
        + " where type = " + addQuotes(BoneComponent::moduleType);    
    
    // query for selecting area actions
    selectControls = "SELECT * FROM " + tabComponents 
        + " where type = " + addQuotes(BoneComponent::actionType);    

    // query for selecting area sensors
    selectSensors = "SELECT * FROM " + tabComponents 
        + " where type = " + addQuotes(BoneComponent::sensorType);    

    btuned = true;
}

bool AreaConnection::readAreaComponents()
{        
    // clear lists
    listModules.clear();  
    listControls.clear();
    listSensors.clear();

    // skip if not yet tuned
    if (!isTuned())
        return false;
    
    // connects to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // gets area modules from DB  & stores them in a list    
    sql::ResultSet* res = oDBClient.read(selectModules);    
    while (res->next())
    {        
       BoneComponent oBoneComponent(res->getInt("id"), BoneComponent::eTYPE_MODULE, res->getString("name"), res->getString("description"));
       listModules.push_back(oBoneComponent);
    }
    delete res;

    // gets area controls from DB  & stores them in a list    
    res = oDBClient.read(selectControls);    
    while (res->next())
    {        
       BoneComponent oBoneComponent(res->getInt("id"), BoneComponent::eTYPE_ACTION, res->getString("name"), res->getString("description"));
       listControls.push_back(oBoneComponent);
    }
    delete res;

    // gets area sensors from DB  & stores them in a list    
    res = oDBClient.read(selectSensors);    
    while (res->next())
    {        
       BoneComponent oBoneComponent(res->getInt("id"), BoneComponent::eTYPE_SENSOR, res->getString("name"), res->getString("description"));
       listSensors.push_back(oBoneComponent);
    }
    delete res;    

    return true;
}

}
}