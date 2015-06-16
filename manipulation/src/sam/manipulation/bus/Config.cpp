/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Config.h"

namespace sam 
{
namespace manipulation 
{
// Constructor
Config::Config ()
{    
    // TEMPORAL: should all be read from a file    

    modulesFreq = 5;  // 5 Hz
}

void Config::init(int robot)
{
    switch (robot)
    {
        case eROBOT_YOUBOT:
            loadYoubot();
            break;
            
        default:
            break;
    }    
}

ParamsJoint& Config::getParamsJoint(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointParams[i].getJointName().compare(jointName) == 0)          
            return oJointParams[i];
    }
      
    // temporal: if not found return the first (should use lists)
    return oJointParams[0];    
}

ParamsJointMover& Config::getParamsJointMover(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointMoverParams[i].getJointName().compare(jointName) == 0)                
            return oJointMoverParams[i];
    }

    // temporal: if not found return the first (should use lists)
    return oJointMoverParams[0];        
}

void Config::loadYoubot()
{    
    int i=0;
    std::string jointName = "shoulderH";
    oJointParams[i].set(jointName, 0, 90, 20);
    oJointMoverParams[i].set(jointName, 3, 10, 3);        
    listJointNames.push_back(jointName);

    i++;
    jointName = "shoulderV";
    oJointParams[i].set(jointName, -30, 160, 20);
    oJointMoverParams[i].set(jointName, 3, 10, 3);
    listJointNames.push_back(jointName);

    i++;
    jointName = "elbow";
    oJointParams[i].set(jointName, -240, -60, 20);
    oJointMoverParams[i].set(jointName, 3, 10, 3);
    listJointNames.push_back(jointName);

    i++;
    jointName = "wrist";
    oJointParams[i].set(jointName, 0, 180, 20);
    oJointMoverParams[i].set(jointName, 3, 10, 3);
    listJointNames.push_back(jointName);

    numJoints = listJointNames.size();
}

}
}
