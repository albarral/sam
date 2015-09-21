#ifndef __SAM_UTILS2_DBCLIENT_H
#define __SAM_UTILS2_DBCLIENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
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
namespace utils2 
{
// Utility class for handling connections to mySql DB servers
class DBClient
{  
private:
    bool binitialized;
    std::string url; // set "tcp://127.0.0.1:3306" as default for mySql servers
    std::string user;
    std::string password;
    std::string schema;
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
        
public:
    DBClient();
    ~DBClient();
    
    void setURL(std::string url) {this->url = url;};
    void init (std::string schema, std::string user, std::string password);
    
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
}

#endif
