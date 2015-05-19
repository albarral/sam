/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ArmManager.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr ArmManager::logger(Logger::getLogger("sam.manipulation"));

// Constructor
ArmManager::ArmManager ()
{    
}

// Destructor
ArmManager::~ArmManager ()
{        
}

void ArmManager::init(std::string armConfigFile)
{
    // TEMPORAL: configuration should be read from the specified file
    
    // create joints (horizontal shoulder, vertical shoulder & elbow)
    Joint oShoulderH;
    Joint oShoulderV;
    Joint oElbow;

    oShoulderH.init(Joint::eJOINT_PAN, 20, -180, 180);    
    oShoulderV.init(Joint::eJOINT_TILT, 20, -45, 90);    
    oElbow.init(Joint::eJOINT_TILT, 20, 0, 90);

    // build the arm (the order is important)
    oArm.addJoint(oShoulderH);
    oArm.addJoint(oShoulderV);
    oArm.addJoint(oElbow);
            
    // create dynamic joint controllers
    JointMover oMoverShoulderH(oShoulderH);
    JointMover oMoverShoulderV(oShoulderV);
    JointMover oMoverElbow(oElbow);

    listJointMovers.push_back(oMoverShoulderH);
    listJointMovers.push_back(oMoverShoulderV);
    listJointMovers.push_back(oMoverElbow);    

    // TO DO ... JointControl modules
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "Arm manager: starting modules ...");
    
    std::vector<JointMover>::iterator it_mover = listJointMovers.begin();
    while (it_mover != listJointMovers.end())
    {
	it_mover->on();
	it_mover++;	
    }

    // TO DO ... launch modules
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "Arm manager: stoppint modules ...");

    // TO DO ... stop & wait for modules 
    
    std::vector<JointMover>::iterator it_mover = listJointMovers.begin();
    while (it_mover != listJointMovers.end())
    {
	it_mover->off();
	it_mover++;	
    }

    it_mover = listJointMovers.begin();
    while (it_mover != listJointMovers.end())
    {
	it_mover->wait();
	it_mover++;	
    }

}
}



