/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "ControlConnection.h"
#include "sam/backbone/config/Config.h"

#include <cppconn/resultset.h>

namespace sam 
{
namespace backbone 
{
ControlConnection::ControlConnection() 
{
    btuned = false;
}

void ControlConnection::setTabMessages(std::string tabName)
{
    this->tabMessages = tabName;

    // query for selecting new messages of the area
    select = "SELECT * FROM " + tabMessages 
        + " where processed = " + std::to_string(ControlMsg::eMSG_NEW);    
    
    // partial query (module needs to be informed)
    updateOK = "UPDATE " + tabMessages    
        + " set processed = " + std::to_string(ControlMsg::eMSG_PROC_OK)
        + " where module_id = ";

    // partial query (module needs to be informed)
    updateKO = "UPDATE " + tabMessages 
        + " set processed = " + std::to_string(ControlMsg::eMSG_PROC_FAILED)
        + " where module_id = ";

    btuned = true;
}

void ControlConnection::readMessages()
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
       ControlMsg oControlMsg(res->getInt("module_id"), res->getInt("action_id"), res->getInt("detail"), res->getInt("priority"), res->getInt("processed"));
       listMessages.push_back(oControlMsg);
    }
 }


bool ControlConnection::writeMessage(ControlMsg& oControlMsg)
{
    // connects to DB 
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set action_id = " + std::to_string(oControlMsg.getActionID())
         + ", detail = " + std::to_string(oControlMsg.getDetail())
         + ", priority = " + std::to_string(oControlMsg.getPriority())
         + ", proc = " + std::to_string(ControlMsg::eMSG_NEW)
        + " where module_id = " + std::to_string(oControlMsg.getModuleID());

    oDBClient.write(update);    
    oDBClient.commit();
    
    return true;
}


//bool ControlConnection::nextMessage()
//{
//    // point to next message in the list
//    index++;
//    if (index < listMessages.size())
//    {
//        pControlMsg = &listMessages.at(index);
//        return true;
//    }
//    
//    // if list finished, false is returned
//    return false;
//}


void ControlConnection::markMessageOk(int moduleID)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // build update ok query
    std::string update = updateOK + std::to_string(moduleID);

    oDBClient.write(update);    
    oDBClient.commit();
}


void ControlConnection::markMessageFailed(int moduleID)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // build update ko query
    std::string update = updateKO + std::to_string(moduleID);

    oDBClient.write(update);    
    oDBClient.commit();
}

}
}