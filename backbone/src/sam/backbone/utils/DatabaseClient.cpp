
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "DatabaseClient.h"

namespace sam 
{
DatabaseClient::DatabaseClient() 
{
    binitialized = false;
    // init pointers
    driver = 0;
    con = 0;
    stmt = 0;
    res = 0;
}

DatabaseClient::~DatabaseClient()
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

void DatabaseClient::init(std::string url, std::string user, std::string password, std::string schema)
{
    driver = get_driver_instance();
    this->url = url;
    this->user = user;
    this->password = password;
    this->schema =schema;
    binitialized = true;    
}

void DatabaseClient::connect()
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

void DatabaseClient::disconnect()
{
    if (con != 0)
    {
        con->close();
        delete con;
        con = 0;
    }
}

sql::ResultSet* DatabaseClient::read(std::string select)
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

void DatabaseClient::write(std::string update)
{ 
    if (isConnected())
    {
        stmt = con->createStatement();   
        stmt->execute(update);  
        delete stmt;        
    }
}

void DatabaseClient::commit()
{     
    if (isConnected())
    {
       con->commit();
    }    
}

void DatabaseClient::rollback()
{     
    if (isConnected())
    {
       con->rollback();
    }    
}
}