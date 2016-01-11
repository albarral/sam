
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/utilsDB/DBClient.h"

namespace sam 
{
namespace utilsDB 
{
DBClient::DBClient(std::string url, std::string schema, std::string user, std::string password) 
{
    this->url = url;
    this->schema =schema;
    this->user = user;
    this->password = password;

    // init pointers
    driver = get_driver_instance();
    con = 0;
    stmt = 0;
    res = 0;
}

DBClient::~DBClient()
{
    // release objects
    //  never delete driver
    disconnect();
    if (con != 0)
        delete con;
    if (res != 0)
        delete res;        
}

void DBClient::connect()
{
    // establish connection with database server 
    if (!isConnected())       
    {
        con = driver->connect(url, user, password);         

        // set the specific database to be used & turn off the autocommit 
        if (!con->isClosed())
        {
            con->setSchema(schema);    
            con->setAutoCommit(0);
        }
    }
}

void DBClient::disconnect()
{
    if (con != 0)
    {
        con->close();
        delete con;
        con = 0;
    }
}

sql::ResultSet* DBClient::read(std::string select)
{  
    if (res != 0)
    {
        delete res;
        res = 0;
    }
    
    if (isConnected())
    {
        stmt = con->createStatement();   
        res = stmt->executeQuery(select);   
        delete stmt;
    }

    return res;
}

void DBClient::write(std::string update)
{ 
    if (isConnected())
    {
        stmt = con->createStatement();   
        stmt->execute(update);  
        delete stmt;        
    }
}

void DBClient::commit()
{     
    if (isConnected())
       con->commit();
}

void DBClient::rollback()
{     
    if (isConnected())
       con->rollback();
}

}
}