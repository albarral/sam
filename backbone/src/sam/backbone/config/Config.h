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

        // arm tables
        std::string tabArmControl;
        std::string tabArmSense;
        std::string tabArmModules;
        std::string tabArmItems;            
        
    public:
        Config();

        std::string getDBServerUrl() {return this->dbServerUrl;};
        std::string getDBUser() {return this->dbUser;};
        std::string getDBPassword() {return this->dbPassword;};
        std::string getDBName() {return this->dbName;};

        std::string getTabArmControl() {return tabArmControl;};
        std::string getTabArmSense() {return tabArmSense;};
        std::string getTabArmModules() {return tabArmModules;};
        std::string getTabArmItems() {return tabArmItems;};
};

}
}    
#endif
