/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BaseConnection.h"

namespace sam 
{  
namespace backbone 
{
BaseConnection::BaseConnection() 
{
    binitialized = false;
}

void BaseConnection::init(Config& oConfig)
{
    // sets database connection params
    oDBClient.setURL(oConfig.getDBServerUrl());
    oDBClient.init(oConfig.getDBName(), oConfig.getDBUser(), oConfig.getDBPassword());    
    binitialized = true;
}

void BaseConnection::close()
{
    if (oDBClient.isConnected())
        oDBClient.disconnect();
}

}
}