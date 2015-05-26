/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ConnectionSet.h"

namespace sam 
{
namespace manipulation 
{
// Constructor
ConnectionSet::ConnectionSet ()
{    
    benabled = false;
}

void ConnectionSet::init(std::string jointName)
{
    this->jointName = jointName;
    benabled = true;    
}

}
}
