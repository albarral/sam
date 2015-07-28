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

        std::string tabAreas;
        std::string tabModules;
        std::string tabSymbols;            
        std::string tabControls;
        std::string tabSenses;
        
    public:
        Config();

        std::string getDBServerUrl() {return this->dbServerUrl;};
        std::string getDBUser() {return this->dbServerUrl;};
        std::string getDBPassword() {return this->dbPassword;};
        std::string getDBName() {return this->dbName;};

        std::string getTabAreas() {return tabAreas;};
        std::string getTabModules() {return tabModules;};
        std::string getTabSymbols() {return tabSymbols;};
        std::string getTabControls() {return tabControls;};
        std::string getTabSenses() {return tabSenses;};
};

}
}    
#endif
