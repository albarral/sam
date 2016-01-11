#ifndef __SAM_UTILSDB_DBCONNECTION_H
#define __SAM_UTILSDB_DBCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/utilsDB/DBClient.h"

namespace sam 
{
namespace utilsDB 
{    
// Base class for management of database connections
// Call to init() needs to be done to use it.    
class DBConnection
{
public:
// supported databases
enum eType
{
    eDB_MYSQL,
    eDB_UNSUPPORTED
};

protected:
    bool binitialized;              // flag to indicate connection parameters are set
    DBClient* oDBClient;         // handler for database connections

public:
    DBConnection();
    //~DBConnection();
    
    // sets connection to local database (of the specified type)
    void init (int type, std::string schema, std::string user, std::string password);
    // sets connection to remote database (of the specified type)
    void init (std::string url, int type, std::string schema, std::string user, std::string password);    
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
