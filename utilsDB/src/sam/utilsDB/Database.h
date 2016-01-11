#ifndef __SAM_UTILSDB_DATABASE_H
#define __SAM_UTILSDB_DATABASE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

namespace sam 
{
namespace utilsDB
{  
class Database
{  
private:
    bool binitialized;
    std::string url; //  "tcp://127.0.0.1:3306";
    std::string user;
    std::string password;
    std::string database;
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    sql::PreparedStatement* prep_stmt;
        
public:
    Database();
    
    void init (std::string url, std::string user, std::string password, std::string database);
    
    bool isInitialized() {return binitialized;};
    void setURL(std::string value) {url = value;}
    void setUser(std::string value1, std::string value2) {user = value1; password = value2;};
    void setTargetDatabase(std::string value) {database = value;};
    
    sql::Connection* getConnectionDB();
    void closeConnectionDB();
    void update(std::string, sql::Connection* con);
    sql::ResultSet* select(std::string, sql::Connection* con);
    
};
}
}

#endif
