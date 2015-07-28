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

void BoneWriter::write(int module, int info, int detail)
{
    // connects to DB 
    if (!oDBClient.isConnected())
        oDBClient.connect();

    // query for updating a specific message in DB
    std::string update = "UPDATE " + tabMessages 
         + " set info = " + std::to_string(info)
         + ", detail = " + std::to_string(detail)
         + ", proc = " + std::to_string(BoneMsg::eMSG_NEW)
        + " where area = " + std::to_string(tunedArea)
        + " and module = " + std::to_string(module);

    oDBClient.write(update);    
    oDBClient.commit();
}


}