/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "ArmManager.h"
#include "sam/manipulation/config/Config.h"
#include "sam/manipulation/bus/Bus.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr ArmManager::logger(Logger::getLogger("sam.manipulation"));

// Constructor
ArmManager::ArmManager ()
{    
    benabled = false;
    level = 0;

    // communications module (listens to console)
    //oComsManip = new ComsManip();
}

// Destructor
ArmManager::~ArmManager ()
{
//    if (oComsManip != 0)
//        delete(oComsManip);
}

void ArmManager::init(std::string robotName)
{
    log4cxx::NDC::push("Arm Manager");   	
    
    LOG4CXX_INFO(logger, "INITIALIZING ... ");
    
    if (oConfig.loadRobot(robotName) == false)
        LOG4CXX_ERROR(logger, "Not enabled !!! Robot not supported: " + robotName);
    
    // obtain (from config file) the list of joints to be controlled 
    std::vector<std::string>& listJointNames = oConfig.getListJointNames();

    initArm(listJointNames);
    initBus(listJointNames);
    initModules(listJointNames);

    // TEMP: first soll angles are 0 (should be the ist)
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++ )
        listSollAngles.push_back(0);    
   
    benabled = true;    
}


void ArmManager::initArm(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, ">> INIT Arm ...");
    
    // build arm with joints
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "joint " << jointName);
        
        // arm's joint
        manipulation::ParamsJoint& mParamsJoint = oConfig.getParamsJoint(jointName);                        
        Joint oJoint; 
        oJoint.init(mParamsJoint);    
        oArm.addJoint(oJoint);                
    }
}


void ArmManager::initBus(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, ">> INIT Bus ...");
    
    // setup connections for each joint
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "joint " << jointName);
        
        if (oBus.add4Joint(jointName) == false)
        {
            LOG4CXX_ERROR(logger, "Error adding bus connection for joint " << jointName);
            return;
        }
    }
}

void ArmManager::initModules(std::vector<std::string>& listJointNames)
{    
    float freq = oConfig.getModulesFreq();

    // init modules FOR each joint
    int numJoints = listJointNames.size();
    
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        // bus connections for this joint
        manipulation::ConnectionsJoint& mConnections4Joint = oBus.getConnectionsJoint(jointName);

        // joint control module
        Joint& mJoint = oArm.getJointByName(jointName);
        oJointControl[i].init(jointName, mJoint);  
        oJointControl[i].connect(mConnections4Joint);
        oJointControl[i].setFrequency(freq);           
    }

    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        // bus connections for this joint
        manipulation::ConnectionsJoint& mConnections4Joint = oBus.getConnectionsJoint(jointName);

        // joint mover module
        manipulation::ParamsJointMover& mParamsJointMover = oConfig.getParamsJointMover(jointName);        
        oJointMover[i].init(jointName, mParamsJointMover);  
        oJointMover[i].connect(mConnections4Joint);
        oJointMover[i].setFrequency(freq);
    }

    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    // arm mover module
    oArmMover.init(3000);
    oArmMover.connect(oBus);
    oArmMover.setFrequency(freq);
    
    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    oArmComs.init(oConfig);
    oArmComs.connect(oBus);
    oArmComs.setFrequency(2);  // 2Hz
    
//    oComsManip->init(oConfig);
//    oComsManip->setFrequency(1); // 1Hz
//    oComsManip->connect(oBus);    
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");
    level = 0;

    if (!benabled)
        return;

    int numJoints = oConfig.getNumJoints();    
    
    LOG4CXX_INFO(logger, ">> START level " << level);
    for (int i=0; i<numJoints; i++)
    {
        if (oJointControl[i].isEnabled() && oJointControl[i].isConnected())
            oJointControl[i].on();
    }

    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
    for (int i=0; i<numJoints; i++)
    {
        if (oJointMover[i].isEnabled() && oJointMover[i].isConnected())
            oJointMover[i].on();
    }
    
    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
    if (oArmMover.isEnabled() && oArmMover.isConnected())
        oArmMover.on();

    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
    if (oArmComs.isEnabled() && oArmComs.isConnected())
        oArmComs.on();
//    if (oComsManip->isEnabled() && oComsManip->isConnected())    
//        oComsManip->on();

}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "STOPPING MODULES ...");

    if (!benabled)
        return;

    int numJoints = oConfig.getNumJoints();    

    LOG4CXX_INFO(logger, ">> STOP level " << level);
    oArmComs.off();
    oArmComs.wait();
//    oComsManip->off();
    //oComsManip->wait();

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    oArmMover.off();
    oArmMover.wait();

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    for (int i=0; i<numJoints; i++)
    {
        // stop & wait for modules 
        if (oJointMover[i].isEnabled())
        {
            oJointMover[i].off();
            oJointMover[i].wait();
        }
    }

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    for (int i=0; i<numJoints; i++)
    {
        // stop & wait for modules 
        if (oJointControl[i].isEnabled()) 
        {
            oJointControl[i].off();
            oJointControl[i].wait();
        }
    }       
}


// Writes to bus
void ArmManager::setIstAngles(std::vector<float>& listAngles)
{
    int size = listAngles.size();
    
    for (int i=0; i<size; i++)
    {
        // write angle in SI_ANGLE
        oBus.getConnectionsJointByIndex(i).getSO_IST_ANGLE().setValue(listAngles.at(i));
    }            
}


// Reads from bus
void ArmManager::readSollAngles()
{        
    int numJoints = oConfig.getNumJoints();       
    float jointAngle;    
    
    // for each joint, check if the commanded angle has changed & insert it into the soll list
    for (int i=0; i<numJoints; i++)
    {        
        if (oBus.getConnectionsJointByIndex(i).getCO_SOLL_ANGLE().checkRequested(jointAngle))
            listSollAngles[i] = jointAngle;
    }
}

bool ArmManager::checkEndRequested()
{
    return oBus.getCO_FINISH_MANAGER().checkRequested();
}

}



