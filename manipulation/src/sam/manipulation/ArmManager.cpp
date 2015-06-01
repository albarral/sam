/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ArmManager.h"
#include "sam/manipulation/bus/Config.h"
#include "sam/manipulation/bus/Connections.h"

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
    
    // get config & connections from bus
    manipulation::Config& mConfig = oBus.getConfig();
    manipulation::Connections& mConnections = oBus.getConnections();

    // obtain (from config file) the list of joints to be controlled 
    std::vector<std::string> listJointNames = mConfig.getListJointNames();

    // initialize the control modules for each joint
    for (int i=0; i<listJointNames.size(); i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "configuring joint " << jointName << " ...");

        // bus connections for joint
        if (mConnections.add4Joint(jointName) == false)
        {
            LOG4CXX_ERROR(logger, "Error adding bus connection for joint " << jointName);
            return;
        }
        manipulation::ConnectionsJoint& mBusConnections4Joint = mConnections.getConnectionsJoint(jointName);
        
        // arm's joint
        manipulation::ParamsJoint& mParamsJoint = mConfig.getParamsJoint(jointName);                        
        Joint oJoint; 
        oJoint.init(mParamsJoint);    
        oArm.addJoint(oJoint);                
        
        // joint mover for joint
        manipulation::ParamsJointMover& mParamsJointMover = mConfig.getParamsJointMover(jointName);        
        oJointMover[i].init(mParamsJointMover);  
        oJointMover[i].connect(mBusConnections4Joint);
        oJointMover[i].setFrequency(mConfig.getModulesFreq());

        // joint control  for joint
        oJointControl[i].init(jointName, oJoint);  
        oJointControl[i].connect(mBusConnections4Joint);
        oJointControl[i].setFrequency(mConfig.getModulesFreq());
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

    if (oJointControl[0].isEnabled() && oJointControl[0].isConnected())
        oJointControl[0].on();
    
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
    
    oJointControl[0].off();
    oJointControl[0].wait();

    oComsManip->off();
    oComsManip->wait();    
}
}



