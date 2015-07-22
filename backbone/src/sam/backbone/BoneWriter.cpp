/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BoneWriter.h"
#include "data/BoneMsg.h"

namespace sam 
{
BoneWriter::BoneWriter() 
{
}

void BoneWriter::write(int moduleID, std::string info, int detail)
{
    BoneMsg oBoneMsg(myAreaID, moduleID, info, detail, BoneMsg::eMSG_NEW);

    // connects to DB if not already done
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set info = " + stringQuotes(oBoneMsg.getInfo())
         + " set detail = " + std::to_string(oBoneMsg.getDetail())
         + " set proc = " + std::to_string(oBoneMsg.getProcessed())
        + " where areaID = " + std::to_string(oBoneMsg.getAreaID())
        + " and moduleID = " + std::to_string(oBoneMsg.getModuleID());

    oDBClient.write(update);    
    oDBClient.commit();
}


}