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

void BoneReader::tune(int direction, std::string areaName)
 {
    BoneBase::tune(direction, areaName);
    
    // query for selecting new messages of the area
    select = "SELECT * FROM " + tabMessages 
        + " where area = " + std::to_string(tunedArea)
        + " and proc = " + std::to_string(BoneMsg::eMSG_NEW);    
    
    // partial query (module needs to be informed)
    updateOK = "UPDATE " + tabMessages    
        + " set proc = " + std::to_string(BoneMsg::eMSG_PROC_OK)
        + " where area = " + std::to_string(tunedArea)
        + " and module = ";

    // partial query (module needs to be informed)
    updateKO = "UPDATE " + tabMessages 
        + " set proc = " + std::to_string(BoneMsg::eMSG_PROC_UNKNOWN)
        + " where area = " + std::to_string(tunedArea)
        + " and module = ";
};


void BoneReader::readMessages()
{        
    // clear messages list
    listMessages.clear();  
    index = -1;
    
    // connects to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // fetches new messages from DB & builds the unprocessed messages list    
    sql::ResultSet* res = oDBClient.read(select);    
    while (res->next())
    {        
       BoneMsg oBoneMsg(res->getInt("area"), res->getInt("module"), res->getInt("info"), res->getInt("detail"));
       listMessages.push_back(oBoneMsg);
    }
    
    //delete res;
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


void BoneReader::markMessageOk(int module)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // build update ok query
    std::string update = updateOK + std::to_string(module);

    oDBClient.write(update);    
    oDBClient.commit();
}


void BoneReader::markMessageFailed(int module)
{
    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // build update ko query
    std::string update = updateKO + std::to_string(module);

    oDBClient.write(update);    
    oDBClient.commit();
}

}