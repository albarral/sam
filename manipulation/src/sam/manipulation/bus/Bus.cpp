/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Bus.h"

namespace sam 
{
namespace manipulation
{
// Constructor
Bus::Bus ()
{    
    benabled = false;
    numJoints = 0;
}

bool Bus::add4Joint(std::string jointName)
{
    // ignore if joint already used
    if (checkExistingJoint(jointName))
        return false;

    if (numJoints < SAM_MAX_JOINTS)
    {
        oConnectionsJoint[numJoints].init(jointName);
        numJoints++;        
        benabled = true;    
        return true;
    }    
    else
        return false;
}

ConnectionsJoint& Bus::getConnectionsJoint(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oConnectionsJoint[i].getJointName().compare(jointName) == 0)
            return oConnectionsJoint[i];
    }
    
    // if not found return the first joint (should use lists)
    return oConnectionsJoint[0];        
}

ConnectionsJoint& Bus::getConnectionsJointByIndex(int index)
{
    if (index < SAM_MAX_JOINTS)
        return oConnectionsJoint[index];
    
    // if not found return the first joint (should use lists)
    return oConnectionsJoint[0];        
}

bool Bus::checkExistingJoint(std::string jointName)
{
    for (int i=0; i<SAM_MAX_JOINTS; i++)
    {
        if (oConnectionsJoint[i].getJointName().compare(jointName) == 0)
            return true;
    }
    
    return false;        
}

}
}
