#ifndef __SAM_NETWORK_CONFIG_H
#define __SAM_NETWORK_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace network 
{
// Configuration parameters for the network area
class Config 
{
    private:                
        // params for connecting to SAM_NETWORK database
        int dbType;
        std::string dbName;
        std::string dbUser;
        std::string dbPassword;

        // names of code tables in DB
        std::string tabArmCodes;     //  ARM area       
        
    public:
        Config();

        int getDBType() {return this->dbType;};
        std::string getDBName() {return this->dbName;};
        std::string getDBUser() {return this->dbUser;};
        std::string getDBPassword() {return this->dbPassword;};

        std::string getArmCodesTable() {return tabArmCodes;};
};

}
}    
#endif
