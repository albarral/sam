/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "DBConnection.h"

namespace sam 
{  
namespace utils2 
{
DBConnection::DBConnection() 
{
    binitialized = false;
    oDBClient = 0;
}

void DBConnection::init(int type, std::string schema, std::string user, std::string password)
{
    // local databases
    switch (type)
    {
        case eDB_MYSQL:
            std::string url = "tcp://127.0.0.1:3306";   // default for local mySql servers
            oDBClient = new DBClient(url, schema, user, password);
            binitialized = true;
            break;
    }            
}

void DBConnection::close()
{
    if (oDBClient->isConnected())
        oDBClient->disconnect();
}

}
}