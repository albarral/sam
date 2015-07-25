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
    
    listRobotNames.push_back("Youbot");    // Kuka Youbot
    listRobotNames.push_back("UR5");        // Universal Robots UR5    
}


bool Config::loadRobot (std::string& robotName)
{
    if (!checkRobotSupported(robotName))
        return false;
        
    if (robotName.compare("Youbot") == 0) 
        loadYoubot();
    else if (robotName.compare("UR5") == 0) 
        loadUR5();
}

bool Config::checkRobotSupported(std::string& robotName)
{
    bool bfound = false;
    // walk the list to find the name
    std::vector<std::string>::iterator it_name = listRobotNames.begin();

    while (it_name != listRobotNames.end())
    {
        if (robotName.compare(*it_name) == 0) 
        {
            bfound = true;
            break;
        }
        it_name++;
    }        
    return bfound;
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
    std::string jointName = "h_shoulder";
    oJointParams[i].set(jointName, 0, 90, 20);
    oJointMoverParams[i].set(jointName, 3, 10, 3);        
    listJointNames.push_back(jointName);

    i++;
    jointName = "v_shoulder";
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

void Config::loadUR5()
{    
    int i=0;
    std::string jointName = "h_shoulder";
    oJointParams[i].set(jointName, -90, 90, 20);    // frontal arm = 0
    oJointMoverParams[i].set(jointName, 15, 40, 30);        
    listJointNames.push_back(jointName);

    i++;
    jointName = "v_shoulder";
    oJointParams[i].set(jointName, 0, 135, 20);     // horizontal arm = 0
    oJointMoverParams[i].set(jointName, 15, 40, 30);
    listJointNames.push_back(jointName);

    i++;
    jointName = "elbow";
    oJointParams[i].set(jointName, -90, 90, 20);     // straight arm = 0
    oJointMoverParams[i].set(jointName, 15, 40, 30);
    listJointNames.push_back(jointName);

    i++;
    jointName = "wrist";
    oJointParams[i].set(jointName, 0, 180, 20);     // straight hand = 90
    oJointMoverParams[i].set(jointName, 15, 40, 30);
    listJointNames.push_back(jointName);

    numJoints = listJointNames.size();
}
}
}
