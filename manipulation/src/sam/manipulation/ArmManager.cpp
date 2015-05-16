/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "ArmManager.h"

#include "sam/manipulation/modules/DynamicMover.h"

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
//    if (oField != NULL)
//        delete (oField);
//    
//    if (oVirBoard != NULL)
//        delete (oVirBoard);
}

void ArmManager::init(std::string armConfigFile)
{
    // TEMPORAL: configuration must be read from the given file
    
    // create joints
    Joint oHShoulder;
    oHShoulder.init(Joint::eJOINT_PAN, 20, -180, 180);    
    Joint oVShoulder;
    oVShoulder.init(Joint::eJOINT_TILT, 20, -45, 90);    
    Joint oElbow;
    oElbow.init(Joint::eJOINT_TILT, 20, 0, 90);

    // build arm (the order is important)
    oArm.addJoint(oHShoulder);
    oArm.addJoint(oVShoulder);
    oArm.addJoint(oElbow);
            
    // create joint controllers
    DynamicMover oDynMoverHShoulder(oHShoulder);
    DynamicMover oDynMoverVShoulder(oVShoulder);
    DynamicMover oDynMoverElbow(oElbow);

    listDynamicMovers.push_back(oDynMoverHShoulder);
    listDynamicMovers.push_back(oDynMoverVShoulder);
    listDynamicMovers.push_back(oDynMoverElbow);    
    
    // TO DO ... PreciseMover and JointControl modules
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "Arm manager: starting modules ...");
    
    // TO DO ... launch modules
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "Arm manager: stoppint modules ...");

    // TO DO ... stop & wait for modules 
}
}



