/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cppconn/resultset.h>

#include "SensorConnection.h"
#include "sam/backbone/config/Config.h"

namespace sam 
{
namespace backbone 
{
SensorConnection::SensorConnection() 
{
    btuned = false;
}

void SensorConnection::tune2Table(std::string tabName)
{
    this->tabMessages = tabName;

    // query for selecting new messages of the area
    select = "SELECT * FROM " + tabMessages;    
    
    btuned = true;
}

bool SensorConnection::readMessages()
{        
    // clear messages list
    listMessages.clear();  
    
    // skip if not yet tuned
    if (!isTuned())
        return false;

    // connects to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // fetches new messages from DB & builds the unprocessed messages list    
    sql::ResultSet* res = oDBClient.read(select);    
    while (res->next())
    {        
       network::SensorMsg oSensorMsg(res->getInt("module_id"), res->getInt("sensor_id"), res->getInt("detail"));
       listMessages.push_back(oSensorMsg);
    }

    return true;
 }

bool SensorConnection::writeMessage(network::SensorMsg& oSensorMsg)
{
    // skip if not yet tuned
    if (!isTuned())
        return false;

    // connects to DB 
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set sensor_id = " + std::to_string(oSensorMsg.getSensorID())
         + ", detail = " + std::to_string(oSensorMsg.getDetail())
         + ", updates += 1" +
         + " where module_id = " + std::to_string(oSensorMsg.getModuleID());

    oDBClient.write(update);    
    oDBClient.commit();
    
    return true;
}

}
}