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
        + " where type = " + addQuotes(network::AreaComponent::moduleType);    
    
    // query for selecting area actions
    selectControls = "SELECT * FROM " + tabComponents 
        + " where type = " + addQuotes(network::AreaComponent::actionType);    

    // query for selecting area sensors
    selectSensors = "SELECT * FROM " + tabComponents 
        + " where type = " + addQuotes(network::AreaComponent::sensorType);    

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
       network::AreaComponent oAreaComponent(res->getInt("id"), network::AreaComponent::eTYPE_MODULE, res->getString("name"));
       listModules.push_back(oAreaComponent);
    }
    delete res;

    // gets area controls from DB  & stores them in a list    
    res = oDBClient.read(selectControls);    
    while (res->next())
    {        
       network::AreaComponent oAreaComponent(res->getInt("id"), network::AreaComponent::eTYPE_ACTION, res->getString("name"));
       listControls.push_back(oAreaComponent);
    }
    delete res;

    // gets area sensors from DB  & stores them in a list    
    res = oDBClient.read(selectSensors);    
    while (res->next())
    {        
       network::AreaComponent oAreaComponent(res->getInt("id"), network::AreaComponent::eTYPE_SENSOR, res->getString("name"));
       listSensors.push_back(oAreaComponent);
    }
    delete res;    

    return true;
}

}
}