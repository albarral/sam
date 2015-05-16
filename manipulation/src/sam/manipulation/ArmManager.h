#ifndef __SAM_ARM_MANAGER_H
#define __SAM_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "sam/manipulation/data/Arm.h"
//#include "sam/manipulation/bus/Config.h"
//#include "sam/manipulation/bus/Connections.h"
//#include "sam/manipulation/modules/ArmMover.h"
#include "sam/manipulation/modules/JointMover.h"
//#include "sam/manipulation/modules/JointControl.h"

namespace sam 
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread.     
class ArmManager
{
    private:
        static log4cxx::LoggerPtr logger;
        //manipulation::Config oConfig;
        //manipulation::Connections oConnections;
        Arm oArm;
        // modules ...
        //ArmMover oArmMover;
        //std::vector<JointMover> listPreciseMovers;    // one for each joint
        std::vector<JointMover> listDynamicMovers;  // one for each joint
        //std::vector<JointControl> listJointControls;  // one for each joint

    public:
        ArmManager();
        ~ArmManager();

        // initializes the arm joints & their controllers given the arm's configuration file
        void init(std::string armConfigFile);
        
        // starts the task's modules 
        void startModules();
        
        // stops the tasks' modules
        void stopModules();        
};

}    
#endif
