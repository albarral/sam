
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "DBClient.h"

namespace sam 
{
namespace utils2 
{
DBClient::DBClient() 
{
    binitialized = false;
    setURL("tcp://127.0.0.1:3306"); // default URL for mysql server
    // init pointers
    driver = 0;
    con = 0;
    stmt = 0;
    res = 0;
}

DBClient::~DBClient()
{
    // release objects
    //  never delete driver
    if (con != 0)
        delete con;
    if (stmt != 0)
        delete stmt;
    if (res != 0)
        delete res;        
}

void DBClient::init(std::string schema, std::string user, std::string password)
{
    this->schema =schema;
    this->user = user;
    this->password = password;
    driver = get_driver_instance();
    binitialized = true;    
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
        delete res;
    
    if (isConnected())
    {
        stmt = con->createStatement();   
        res = stmt->executeQuery(select);   
        delete stmt;
    }
    else
        res = 0;

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