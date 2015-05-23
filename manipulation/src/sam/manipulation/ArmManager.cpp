/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ArmManager.h"
#include "sam/manipulation/bus/Config.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr ArmManager::logger(Logger::getLogger("sam.manipulation"));

// Constructor
ArmManager::ArmManager ()
{    
    init();
}

// Destructor
ArmManager::~ArmManager ()
{        
}

void ArmManager::init()
{
    manipulation::Config& mConfig = oBus.getConfig();
    
    // build the arm ...
    // Horizontal shoulder
    Joint oShoulderH; 
    oShoulderH.init(Joint::eJOINT_PAN, mConfig.getShoulderHParams());    
    if (oShoulderH.isEnabled())
        oArm.addJoint(oShoulderH);
    /*
    // Vertical shoulder
    Joint oShoulderV; 
    oShoulderV.init(Joint::eJOINT_TILT, mConfig.getShoulderVParams());    
    if (oShoulderV.isEnabled())
        oArm.addJoint(oShoulderV);
    // Elbow
    Joint oElbow;       
    oElbow.init(Joint::eJOINT_TILT, mConfig.getElbowParams());
    if (oElbow.isEnabled())
        oArm.addJoint(oElbow);
    */
    
    // setup the joint controllers
    // Horizontal shoulder
    oShoulderMoverH = new JointMover();
    oShoulderMoverH->init("shoulder", mConfig.getShoulderMoverHParams());
    oShoulderMoverH->setFrequency(mConfig.getModulesFreq());
    oShoulderMoverH->connect(oBus);
    // Vertical shoulder (to do ...)
    // Elbow (to do ...)
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "Arm manager: starting modules ...");
    
    if (oShoulderMoverH->isEnabled() && oShoulderMoverH->isConnected())
        oShoulderMoverH->on();
    
//    std::vector<JointMover>::iterator it_mover = listJointMovers.begin();
//    while (it_mover != listJointMovers.end())
//    {
//	it_mover->on();
//	it_mover++;	
//    }

    // TO DO ... launch modules
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "Arm manager: stopping modules ...");

    // stop & wait for modules 
    oShoulderMoverH->off();
    oShoulderMoverH->wait();
    
//    std::vector<JointMover>::iterator it_mover = listJointMovers.begin();
//    while (it_mover != listJointMovers.end())
//    {
//	it_mover->off();
//	it_mover++;	
//    }
//
//    it_mover = listJointMovers.begin();
//    while (it_mover != listJointMovers.end())
//    {
//	it_mover->wait();
//	it_mover++;	
//    }

}
}



