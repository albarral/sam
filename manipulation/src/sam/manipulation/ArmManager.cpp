/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

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
    benabled = false;

    // communications module (listens to console)
    oComsManip = new ComsManip();
}

// Destructor
ArmManager::~ArmManager ()
{
    if (oComsManip != 0)
        delete(oComsManip);
}

void ArmManager::init(std::string robotName)
{
    log4cxx::NDC::push("Arm Manager");   	
    LOG4CXX_INFO(logger, "init ...");
    
    if (oBus.getConfig().loadRobot(robotName) == false)
        LOG4CXX_ERROR(logger, "Not enabled !!! Robot not supported: " + robotName);
    
    // obtain (from config file) the list of joints to be controlled 
    std::vector<std::string> listJointNames = oBus.getConfig().getListJointNames();

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
    LOG4CXX_INFO(logger, "init Arm ...");
    
    // get config
    manipulation::Config& mConfig = oBus.getConfig();

    // build arm with joints
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "joint " << jointName);
        
        // arm's joint
        manipulation::ParamsJoint& mParamsJoint = mConfig.getParamsJoint(jointName);                        
        Joint oJoint; 
        oJoint.init(mParamsJoint);    
        oArm.addJoint(oJoint);                
    }
    
    LOG4CXX_INFO(logger, "Arm ok!");
}


void ArmManager::initBus(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, "init Bus ...");
    
    // get bus connections
    manipulation::Connections& mConnections = oBus.getConnections();

    // setup connections for each joint
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "joint " << jointName);
        
        if (mConnections.add4Joint(jointName) == false)
        {
            LOG4CXX_ERROR(logger, "Error adding bus connection for joint " << jointName);
            return;
        }
    }
    
    LOG4CXX_INFO(logger, "Bus ok!");
}

void ArmManager::initModules(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, "init modules ...");
    
    // get config
    manipulation::Config& mConfig = oBus.getConfig();
    float freq = mConfig.getModulesFreq();
    // get bus connections
    manipulation::Connections& mConnections = oBus.getConnections();

    // init modules for each joint
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, "modules for joint " << jointName << " ... ");
        
        // bus connections for this joint
        manipulation::ConnectionsJoint& mConnections4Joint = mConnections.getConnectionsJoint(jointName);

        // joint mover module
        manipulation::ParamsJointMover& mParamsJointMover = mConfig.getParamsJointMover(jointName);        
        oJointMover[i].init(jointName, mParamsJointMover);  
        oJointMover[i].connect(mConnections4Joint);
        oJointMover[i].setFrequency(freq);

        // joint control module
        Joint& mJoint = oArm.getJointByName(jointName);
        oJointControl[i].init(jointName, mJoint);  
        oJointControl[i].connect(mConnections4Joint);
        oJointControl[i].setFrequency(freq);           
    }
        
    // arm mover module
    oArmMover.init(3000);
    oArmMover.connect(mConnections);
    oArmMover.setFrequency(freq);
    
    oComsManip->init();
    oComsManip->setFrequency(1); // 1Hz
    oComsManip->connect(oBus);    

    LOG4CXX_INFO(logger, "modules ok!");
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "Arm manager: starting modules ...");

    if (!benabled)
        return;
    
    int numJoints = oBus.getConfig().getNumJoints();    
    for (int i=0; i<numJoints; i++)
    {
        if (oJointControl[i].isEnabled() && oJointControl[i].isConnected())
            oJointControl[i].on();

        if (oJointMover[i].isEnabled() && oJointMover[i].isConnected())
            oJointMover[i].on();
    }

    if (oComsManip->isEnabled() && oComsManip->isConnected())    
        oComsManip->on();
    
    if (oArmMover.isEnabled() && oArmMover.isConnected())
        oArmMover.on();
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "Arm manager: stopping modules ...");

    if (!benabled)
        return;

    int numJoints = oBus.getConfig().getNumJoints();    
    for (int i=0; i<numJoints; i++)
    {
        // stop & wait for modules 
        if (oJointMover[i].isEnabled())
        {
            oJointMover[i].off();
            oJointMover[i].wait();
        }

        if (oJointControl[i].isEnabled()) 
        {
            oJointControl[i].off();
            oJointControl[i].wait();
        }
    }

    oComsManip->off();
    oComsManip->wait();
    
    oArmMover.off();
    oArmMover.wait();
}


// Writes to bus
void ArmManager::setIstAngles(std::vector<float>& listAngles)
{
    manipulation::Connections& mConnections = oBus.getConnections();
    int size = listAngles.size();
    
    for (int i=0; i<size; i++)
    {
        // write angle in SI_ANGLE
        mConnections.getConnectionsJointByIndex(i).getSOIst().setValue(listAngles.at(i));
    }            
}


// Reads from bus
void ArmManager::readSollAngles()
{        
    manipulation::Connections& mConnections = oBus.getConnections();
    int numJoints = oBus.getConfig().getNumJoints();       
    float jointAngle;    
    
    // for each joint, check if the commanded angle has changed & insert it into the soll list
    for (int i=0; i<numJoints; i++)
    {        
        if (mConnections.getConnectionsJointByIndex(i).getCOAngle().checkRequested(jointAngle))
            listSollAngles[i] = jointAngle;
    }
}

bool ArmManager::checkEndRequested()
{
    return oBus.getConnections().getCOFinish().checkRequested();
}

}



