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
   
    tabAreas = "TAB_AREAS";
    tabModules = "TAB_MODULES";
    tabSymbols = " TAB_SYMBOLS";
    tabControls = "TAB_CONTROLS";
    tabSenses = "TAB_SENSES";
}

}
}
