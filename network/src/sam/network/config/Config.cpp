/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Config.h"
#include "sam/utils2/DBConnection.h"

namespace sam 
{
namespace network 
{
// Constructor
Config::Config ()
{               
    dbType = utils2::DBConnection::eDB_MYSQL;   // use mysql DB server
    dbName = "SAM_NETWORK";
    dbUser = "sam";
    dbPassword = "sam";
   
    tabArmCodes = " TAB_ARM_CODES";
}

}
}
