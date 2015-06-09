#ifndef __SAM_ARM_MANAGER_H
#define __SAM_ARM_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "sam/manipulation/data/defines.h"
#include "sam/manipulation/bus/Bus.h"
#include "sam/manipulation/data/Arm.h"
//#include "sam/manipulation/modules/ArmMover.h"
#include "sam/manipulation/modules/JointMover.h"
#include "sam/manipulation/modules/JointControl.h"
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
        JointMover oJointMover[SAM_MAX_JOINTS];
        JointControl oJointControl[SAM_MAX_JOINTS];
        //ArmMover oArmMover;
        ComsManip* oComsManip;
        // system's output
        std::vector<float> listSollAngles;

    public:
        ArmManager();
        ~ArmManager();

        // initializes everything (arm, bus & modules)
        void init();        
        // starts the task's modules 
        void startModules();        
        // stops the tasks' modules
        void stopModules();        
        
        // returns commanded positions for all arm joints (in degrees)
        std::vector<float>& getMoves();
        
private:
    void initArm(std::vector<std::string>& listJointNames);
    void initBus(std::vector<std::string>& listJointNames);
    void initModules(std::vector<std::string>& listJointNames);
};

}    
#endif
