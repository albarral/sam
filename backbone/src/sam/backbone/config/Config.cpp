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
   
    tabArmControl = "TAB_ARM_CONTROL";
    tabArmSense = "TAB_ARM_SENSE";
    tabArmModules = "TAB_ARM_MODULES";
    tabArmItems = " TAB_ARM_ITEMS";
}

}
}
