#ifndef __SAM_ARM_MANAGER_H
#define __SAM_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <vector>
#include <log4cxx/logger.h>

#include "sam/manipulation/bus/Bus.h"
#include "sam/manipulation/data/Arm.h"
//#include "sam/manipulation/modules/ArmMover.h"
#include "sam/manipulation/modules/JointMover.h"
#include "sam/manipulation/modules/ComsManip.h"

namespace sam 
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread.     
class ArmManager
{
    private:
        static log4cxx::LoggerPtr logger;
        manipulation::Bus oBus;
        Arm oArm;
        // modules ...
        JointMover* oShoulderMoverH;
        //ArmMover oArmMover;
        ComsManip* oComsManip;
        //std::vector<JointControl> listJointControls;  // one for each joint

    public:
        ArmManager();
        ~ArmManager();

        // initializes the arm joints & their controllers
        void init();
        
        // starts the task's modules 
        void startModules();
        
        // stops the tasks' modules
        void stopModules();        
};

}    
#endif
