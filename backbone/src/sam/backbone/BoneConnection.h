#ifndef __SAM_BACKBONE_BONECONNECTION_H
#define __SAM_BACKBONE_BONECONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "config/Config.h"
#include "utils2/DBClient.h"

namespace sam 
{
namespace backbone 
{    
// Base class for management of backbone communication.
// It handles connections to the backbone DB.
// Call to init() needs to be done to use it.    
class BoneConnection
{
protected:
    bool binitialized;              // flag to indicate connection parameters are set
    Config oConfig;
    utils2::DBClient oDBClient;          // handler for database connections

public:
    BoneConnection();
    
    // sets connection parameters for the database client handler
    void init ();
    bool isInitialized() {return binitialized;};        
    // closes connection to DB
    void close();   

protected:    
     // add initial & final quotes to a given string
    std::string addQuotes(std::string word) {return "'"+word+"'";};
};
}
}

#endif
