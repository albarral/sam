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
    LOG4CXX_INFO(logger, "Arm manager: init ...");
    
    // read config
    manipulation::Config& mConfig = oBus.getConfig();

    // set bus connections
    oBus.getConnections().init(mConfig.getListJointNames());
       
    // build arm & modules joint by joint ...
    int numJoints = mConfig.getNumJoints();
    for (int i=0; i<numJoints; i++)
    {        
        // arm
        Joint oJoint; 
        oJoint.init(mConfig.getJointParams(i));    
        oArm.addJoint(oJoint);
                
        // joint mover modules
        oJointMover[i].init(mConfig.getJointMoverParams(i));  
        oJointMover[i].setFrequency(mConfig.getModulesFreq());
        oJointMover[i].connect(oBus);
    }
        
    // communications module (listens to console)
    oComsManip = new ComsManip();
    oComsManip->init();
    oComsManip->setFrequency(1); // 1Hz
    oComsManip->connect(oBus);    
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "Arm manager: starting modules ...");
    
    if (oJointMover[0].isEnabled() && oJointMover[0].isConnected())
        oJointMover[0].on();
    
    if (oComsManip->isEnabled() && oComsManip->isConnected())
        oComsManip->on();
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "Arm manager: stopping modules ...");

    // stop & wait for modules 
    oJointMover[0].off();
    oJointMover[0].wait();
    
    oComsManip->off();
    oComsManip->wait();    
}
}



