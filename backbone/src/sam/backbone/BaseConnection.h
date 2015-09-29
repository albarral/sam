#ifndef __SAM_BACKBONE_BASECONNECTION_H
#define __SAM_BACKBONE_BASECONNECTION_H

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
class BaseConnection
{
protected:
    bool binitialized;              // flag to indicate connection parameters are set
    utils2::DBClient oDBClient;          // handler for database connections

public:
    BaseConnection();
    
    // sets connection parameters for the database client handler
    void init (Config& oConfig);
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
