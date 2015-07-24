/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Config.h"

namespace sam 
{
namespace backbone 
{
// Constructor
Config::Config ()
{               
    dbServerUrl = "tcp://127.0.0.1:3306"; // mysql server
    dbUser = "sam";
    dbPassword = "sam";
    dbName = "SAM_BACKBONE";
   
    tabNameAreas = "TAB_AREAS";
    tabNameModules = "TAB_MODULES";
    tabNameCommands = "TAB_COMMANDS";
    tabNameInfo = "TAB_INFO";
}

}
}
