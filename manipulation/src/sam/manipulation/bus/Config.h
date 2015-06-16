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
public:
    enum eROBOT
    {
        eROBOT_YOUBOT,
        eROBOT_OWI,
        eROBOT_UNKNOWN
    };
    
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

        // initializes the configuration for the given robot
        void init (int robot);
        
        int getNumJoints() {return numJoints;};
        
        std::vector<std::string>& getListJointNames() {return listJointNames;};
        
        float getModulesFreq () {return modulesFreq;}        
        
        // gets the Joint module paramaters for the given joint name
        ParamsJoint& getParamsJoint(std::string jointName);
        // gets the JointMover module paramaters for the given joint name
        ParamsJointMover& getParamsJointMover(std::string jointName);
        
private:
    void loadYoubot();
    // void loadOwi();
};

}
}    
#endif
