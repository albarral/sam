/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ConnectionsJoint.h"

namespace sam 
{
namespace manipulation 
{
// Constructor
ConnectionsJoint::ConnectionsJoint ()
{    
    benabled = false;
}

void ConnectionsJoint::init(std::string jointName)
{
    this->jointName = jointName;
    benabled = true;    
}

}
}
