
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace utilsDB
{     
Database::Database() 
{
    binitialized = false;

    res = 0;
}

void Database::init(std::string url, std::string user, std::string password, std::string database)
{
    setURL(url);
    setUser(user, password);
    setTargetDatabase(database);
    binitialized = true;    
}

sql::Connection* Database::getConnectionDB()
{
    driver = get_driver_instance();
    con = driver->connect(url, user, password); 
    // leave autocommit set, otherwise consecutive selects won't change
    //con->setAutoCommit(0);    // turn off the autocommit 
    
    return con;
}

void Database::closeConnectionDB()
{
    con->close();
    delete con;
}

void Database::update(std::string insert, sql::Connection* con)
{ 
    con->setSchema(database);    
    prep_stmt = con->prepareStatement (insert);    
    prep_stmt->execute();  
    delete prep_stmt;
}

sql::ResultSet* Database::select(std::string sel, sql::Connection* con)
{  
    if (res != 0)
        delete res;
    
    con->setSchema(database);   
    stmt = con->createStatement();   
    res = stmt->executeQuery(sel);   
    delete stmt;

    return res;
}

}
}