/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cppconn/resultset.h>

#include "CodesConnection.h"
#include "sam/backbone/config/Config.h"
#include "utils2/DBClient.h"

namespace sam 
{
namespace backbone 
{
CodesConnection::CodesConnection() 
{
    btuned = false;
}

void CodesConnection::tune2Table(std::string tabName)
{
    this->tabNetworkCodes = tabName;

    // query for selecting area modules
    selectNetModules = "SELECT * FROM " + tabNetworkCodes 
        + " where type = " + addQuotes(network::NetworkCode::typeModule);    
    
    // query for selecting area actions
    selectNetControls = "SELECT * FROM " + tabNetworkCodes 
        + " where type = " + addQuotes(network::NetworkCode::typeAction);    

    // query for selecting area sensors
    selectNetSensors = "SELECT * FROM " + tabNetworkCodes 
        + " where type = " + addQuotes(network::NetworkCode::typeSensor);    

    btuned = true;
}

bool CodesConnection::readNetworkCodes()
{        
    // clear lists
    listNetModules.clear();  
    listNetControls.clear();
    listNetSensors.clear();

    // skip if not yet tuned
    if (!isTuned())
        return false;
    
    // connects to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // gets area modules from DB  & stores them in a list    
    sql::ResultSet* res = oDBClient.read(selectNetModules);    
    while (res->next())
    {        
       network::NetworkCode oNetworkCode(res->getInt("id"), network::NetworkCode::eTYPE_MODULE, res->getString("name"));
       listNetModules.push_back(oNetworkCode);
    }
    delete res;

    // gets area controls from DB  & stores them in a list    
    res = oDBClient.read(selectNetControls);    
    while (res->next())
    {        
       network::NetworkCode oNetworkCode(res->getInt("id"), network::NetworkCode::eTYPE_ACTION, res->getString("name"));
       listNetControls.push_back(oNetworkCode);
    }
    delete res;

    // gets area sensors from DB  & stores them in a list    
    res = oDBClient.read(selectNetSensors);    
    while (res->next())
    {        
       network::NetworkCode oNetworkCode(res->getInt("id"), network::NetworkCode::eTYPE_SENSOR, res->getString("name"));
       listNetSensors.push_back(oNetworkCode);
    }
    delete res;    

    return true;
}

}
}