#ifndef __SAM_MANIPULATION_CONFIG_H
#define __SAM_MANIPULATION_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

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
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        // joints
        ParamsJoint oShoulderHParams;   // horizontal shoulder
        ParamsJoint oShoulderVParams;   // vertical shoulder
        ParamsJoint oElbowParams;         // elbow
        // joint movers
        ParamsJointMover oShoulderMoverHParams;
        ParamsJointMover oShoulderMoverVParams;
        ParamsJointMover oElbowMoverParams;
        
    public:
        Config();

        float getModulesFreq () {return modulesFreq;}        
        // joints
        ParamsJoint& getShoulderHParams() {return oShoulderHParams;};
        ParamsJoint& getShoulderVParams() {return oShoulderVParams;};
        ParamsJoint& getElbowParams() {return oElbowParams;};
        // joint movers
        ParamsJointMover& getShoulderMoverHParams() {return oShoulderMoverHParams;};
        ParamsJointMover& getShoulderMoverVParams() {return oShoulderMoverVParams;};
        ParamsJointMover& getElbowMoverParams() {return oElbowMoverParams;};
};

}
}    
#endif
