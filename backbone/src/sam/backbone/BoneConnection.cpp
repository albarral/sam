/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BoneConnection.h"

namespace sam 
{  
namespace backbone 
{
BoneConnection::BoneConnection() 
{
    binitialized = false;
}

void BoneConnection::init(Config& oConfig)
{
    // sets database connection params
    oDBClient.setURL(oConfig.getDBServerUrl());
    oDBClient.init(oConfig.getDBName(), oConfig.getDBUser(), oConfig.getDBPassword());    
    binitialized = true;
}

void BoneConnection::close()
{
    if (oDBClient.isConnected())
        oDBClient.disconnect();
}

}
}