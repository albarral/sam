#ifndef __SAM_MANIPULATION_CONFIG_H
#define __SAM_MANIPULATION_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/manipulation/data/defines.h"
#include "sam/manipulation/bus/ParamsJoint.h"
#include "sam/manipulation/bus/ParamsJointMover.h"

namespace sam 
{
namespace manipulation 
{
class Config 
{
    private:                
        std::string configFile;     // name of config file  (not used yet)
        int numJoints;
        std::vector<std::string> listJointNames;
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // joints
        ParamsJoint oJointParams[SAM_MAX_JOINTS];
        // joint movers
        ParamsJointMover oJointMoverParams[SAM_MAX_JOINTS];
        
    public:
        Config();

        int getNumJoints() {return numJoints;};
        std::vector<std::string>& getListJointNames() {return listJointNames;};
        float getModulesFreq () {return modulesFreq;}        
        
        // joints
        ParamsJoint& getJointParams(int index);
        // joint movers
        ParamsJointMover& getJointMoverParams(int index);
};

}
}    
#endif