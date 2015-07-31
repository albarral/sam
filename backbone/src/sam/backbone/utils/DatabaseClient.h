#ifndef __SAM_UTILS_DATABASECLIENT_H
#define __SAM_UTILS_DATABASECLIENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>

#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

namespace sam 
{
class DatabaseClient
{  
private:
    bool binitialized;
    std::string url; //  "tcp://127.0.0.1:3306" for mySql
    std::string user;
    std::string password;
    std::string schema;
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
        
public:
    DatabaseClient();
    ~DatabaseClient();
    
    void init (std::string url, std::string user, std::string password, std::string schema);
    
    bool isInitialized() {return binitialized;};
    bool isConnected() {return (con != 0 && !con->isClosed());};
        
    void connect();
    void disconnect();
    
    sql::ResultSet* read(std::string select);
    void write(std::string update);

    void commit();
    void rollback();
};
}

#endif
