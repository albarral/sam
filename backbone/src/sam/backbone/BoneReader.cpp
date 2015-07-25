/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BoneReader.h"

namespace sam 
{
BoneReader::BoneReader() 
{
    pBoneMsg = 0;
}

void BoneReader::tune(int direction, std::string area)
 {
    BoneBase::tune(direction, area);
    
    // query for selecting new messages of the area
    select = "SELECT * FROM " + tabMessages 
        + " where areaID = " + std::to_string(tunedAreaID)
        + " and proc = " + std::to_string(BoneMsg::eMSG_NEW);    
};


void BoneReader::readMessages()
{        
    // clear list of messages
    listMessages.clear();  
    index = -1;
    
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // fetches new messages from DB & builds the unprocessed messages list    
    sql::ResultSet* res = oDBClient.read(select);    
    while (res->next())
    {        
       BoneMsg oBoneMsg(res->getInt("areaID"), res->getInt("moduleID"), res->getString("info"), res->getInt("detail"));
       listMessages.push_back(oBoneMsg);
    }
 }


bool BoneReader::nextMessage()
{
    // point to next message in the list
    index++;
    if (index < listMessages.size())
    {
        pBoneMsg = &listMessages.at(index);
        return true;
    }
    
    // if list finished, false is returned
    return false;
}


void BoneReader::markMessageOk(int moduleID)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set proc = " + std::to_string(BoneMsg::eMSG_PROC_OK)
        + " where areaID = " + std::to_string(tunedAreaID)
        + " and moduleID = " + std::to_string(moduleID);

    oDBClient.write(update);    
    oDBClient.commit();
}


void BoneReader::markMessageFailed(int moduleID)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set proc = " + std::to_string(BoneMsg::eMSG_PROC_UNKNOWN)
        + " where areaID = " + std::to_string(tunedAreaID)
        + " and moduleID = " + std::to_string(moduleID);

    oDBClient.write(update);    
    oDBClient.commit();
}

}