/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cppconn/resultset.h>

#include "DBAreaCodes.h"
#include "sam/network/config/Config.h"
#include "sam/utils2/DBClient.h"

namespace sam 
{
namespace network 
{
DBAreaCodes::DBAreaCodes() 
{
    btuned = false;
   
    // initialize connection to network DB
    Config oNetworkConfig;
    init(oNetworkConfig.getDBType(), oNetworkConfig.getDBName(), oNetworkConfig.getDBUser(), oNetworkConfig.getDBPassword());   
}

void DBAreaCodes::tune2Table(std::string tabName)
{
    this->tabAreaCodes = tabName;

    // query for selecting an area's codes
    selectAreaCodes = "SELECT * FROM " + tabAreaCodes;
    
    btuned = true;
}

bool DBAreaCodes::readAreaCodes()
{        
    // clear lists
    listAreaCodes.clear();  

    // skip if not yet tuned
    if (!isTuned())
        return false;
    
    // connects to DB
    if (!oDBClient->isConnected())
        oDBClient->connect();
    
    // gets area modules from DB  & stores them in a list    
    sql::ResultSet* res = oDBClient->read(selectAreaCodes);    
    while (res->next())
    {        
       NetworkCode oNetworkCode(res->getInt("id"), res->getInt("type"), res->getString("name"));
       listAreaCodes.push_back(oNetworkCode);
    }
    delete res;

    return true;
}

}
}