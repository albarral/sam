
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
    bconnected = false;
    // init pointers
    driver = 0;
    con = 0;
    stmt = 0;
    res = 0;
    prep_stmt = 0;
}

DatabaseClient::~DatabaseClient()
{
    // release objects
//    if (driver != 0)
//        delete (driver);
    if (con != 0)
        delete (con);
    if (stmt != 0)
        delete (stmt);
    if (res != 0)
        delete (res);        
    if (prep_stmt != 0)
        delete (prep_stmt);
}

void DatabaseClient::init(std::string url, std::string user, std::string password, std::string schema)
{
    this->url = url;
    this->user = user;
    this->password = password;
    this->schema =schema;
    binitialized = true;    
}

void DatabaseClient::connect()
{
    // establish connection with database server & set database to be used
    driver = get_driver_instance();
    con = driver->connect(url, user, password); 
    
    if (con != 0)
    {
        con->setSchema(schema);    
        // also turn off the autocommit (user must commit after each transaction set)
        con->setAutoCommit(0);
        bconnected = true;
    }
    // else throw exception
}

void DatabaseClient::disconnect()
{
    if (con != 0)
    {
        con->close();
        delete con;
        bconnected = false;
    }
}

void DatabaseClient::write(std::string update)
{ 
    if (bconnected)
    {
        prep_stmt = con->prepareStatement(update);    
        prep_stmt->execute();  
        delete prep_stmt;        
    }
}

sql::ResultSet* DatabaseClient::read(std::string select)
{  
    if (bconnected)
    {
        stmt = con->createStatement();   
        res = stmt->executeQuery(select);   
        delete stmt;
    }
    else
        res = 0;

    return res;
}

void DatabaseClient::commit()
{     
    if (bconnected)
    {
       con->commit();
    }    
}

void DatabaseClient::rollback()
{     
    if (bconnected)
    {
       con->rollback();
    }    
}
}