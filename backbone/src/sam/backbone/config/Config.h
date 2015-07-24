#ifndef __SAM_BACKBONE_CONFIG_H
#define __SAM_BACKBONE_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace backbone 
{
// Class for reading the configuration of the Backbone system (to do ... from a file)    
class Config 
{
    private:                
        // params for connecting to the backbone database
        std::string dbServerUrl;
        std::string dbUser;
        std::string dbPassword;
        std::string dbName;

        std::string tabNameAreas;
        std::string tabNameModules;
        std::string tabNameCommands;
        std::string tabNameInfo;
        
    public:
        Config();

        std::string getDBServerUrl() {return this->dbServerUrl;};
        std::string getDBUser() {return this->dbServerUrl;};
        std::string getDBPassword() {return this->dbPassword;};
        std::string getDBName() {return this->dbName;};

        std::string getTabNameAreas() {return tabNameAreas;};
        std::string getTabNameModules() {return tabNameModules;};
        std::string getTabNameCommands() {return tabNameCommands;};
        std::string getTabNameInfo() {return tabNameInfo;};
};

}
}    
#endif
