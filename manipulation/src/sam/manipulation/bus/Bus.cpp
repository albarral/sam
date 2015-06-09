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
    numJoints = oConfig.getNumJoints();
}

// Destructor
Bus::~Bus ()
{        
}

void Bus::getSollAngles(std::vector<float>& listSollAngles)
{
    float jointAngle;
    
    listSollAngles.clear();
    for (int i=0; i<numJoints; i++)
    {        
        oConnections.getConnectionsJointByIndex(i).getCOAngle().isRequested(jointAngle);
        listSollAngles.push_back(jointAngle);
    }
}

}
}



