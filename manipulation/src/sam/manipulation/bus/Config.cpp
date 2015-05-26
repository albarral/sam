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

    listJointNames.push_back("shoulderH");
//    listJointNames.push_back("shoulderV");        
//    listJointNames.push_back("elbow");

    int i=0;
    // important: use same name for joints & joint movers
    std::string name = listJointNames.at(i);
    oJointParams[i].set(name, -180, 180, 20);
    oJointMoverParams[i].set(name, 3, 10, 3);
    i++;

//    name = listJointNames.at(i);
//    oJointParams[i].set(name, -45, 90, 20);
//    oJointMoverParams[i].set(name, 3, 10, 3);
//    i++;
//
//    name = listJointNames.at(i);
//    oJointParams[i].set(name, 0, 90,20);
//    oJointMoverParams[i].set(name, 3, 10, 3);
//    i++;
    
    numJoints = i;
}

ParamsJoint& Config::getJointParams(int index)
{
    if (index < numJoints)
        return oJointParams[index];
    else
        // temporal: if not found return the first (should use lists)
        return oJointParams[0];    
}

ParamsJointMover& Config::getJointMoverParams(int index)
{
    if (index < numJoints)
        return oJointMoverParams[index];
    else
        // temporal: if not found return the first (should use lists)
        return oJointMoverParams[0];        
}

}
}
