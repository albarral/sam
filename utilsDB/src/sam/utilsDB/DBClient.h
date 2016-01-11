#ifndef __SAM_UTILSDB_DBCLIENT_H
#define __SAM_UTILSDB_DBCLIENT_H

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
namespace utilsDB 
{
// Utility class for handling connections to mySql DB servers
class DBClient
{  
private:
    std::string url; 
    std::string user;
    std::string password;
    std::string schema;
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
        
public:
    DBClient(std::string url, std::string schema, std::string user, std::string password);
    ~DBClient();
            
    void connect();
    void disconnect();
    bool isConnected() {return (con != 0 && !con->isClosed());};
    
    sql::ResultSet* read(std::string select);
    void write(std::string update);

    void commit();
    void rollback();
};
}
}

#endif
