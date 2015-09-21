/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "SensorConnection.h"
#include "sam/backbone/config/Config.h"

#include <cppconn/resultset.h>

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

void SensorConnection::readMessages()
{        
    // clear messages list
    listMessages.clear();  
    
    // connects to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // fetches new messages from DB & builds the unprocessed messages list    
    sql::ResultSet* res = oDBClient.read(select);    
    while (res->next())
    {        
       SensorMsg oSensorMsg(res->getInt("module_id"), res->getInt("sensor_id"), res->getInt("detail"), res->getInt("updates"));
       listMessages.push_back(oSensorMsg);
    }
 }

bool SensorConnection::writeMessage(SensorMsg& oSensorMsg)
{
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

//bool SensorConnection::nextMessage()
//{
//    // point to next message in the list
//    index++;
//    if (index < listMessages.size())
//    {
//        pSensorMsg = &listMessages.at(index);
//        return true;
//    }
//    
//    // if list finished, false is returned
//    return false;
//}

}
}