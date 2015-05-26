/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Connections.h"

namespace sam 
{
namespace manipulation
{
// Constructor
Connections::Connections ()
{    
    benabled = false;
    numJoints = 0;
}

void Connections::init(std::vector<std::string> listJointNames)
{
    std::string jointName; 
    
    // init each joint connection set
    for (int i=0; i<listJointNames.size(); i++)
    {
        jointName = listJointNames.at(i);
        oJointConnections[i].init(jointName);
        numJoints++;
    }        

    benabled = true;    
}

ConnectionSet& Connections::getJointConnections(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointConnections[i].getJointName().compare(jointName) == 0)
            return oJointConnections[i];
    }
    
    // if not found return the first joint (should use lists)
    return oJointConnections[0];        
}

}
}
