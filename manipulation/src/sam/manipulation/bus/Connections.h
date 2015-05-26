#ifndef __SAM_MANIPULATION_CONNECTIONS_H
#define __SAM_MANIPULATION_CONNECTIONS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/manipulation/data/defines.h"
#include "sam/manipulation/bus/ConnectionSet.h"

namespace sam 
{
namespace manipulation 
{    
class Connections
{
    private:        
        bool benabled;
        ConnectionSet oJointConnections[SAM_MAX_JOINTS];
        int numJoints;   // number of active joints
        
    public:
        Connections();
        //~Connections();

        // initializes the JointConnections, each with a given joint name
        void init (std::vector<std::string> listJointNames);        
        bool isEnabled() {return benabled;};
        
        // gets the connections set for the specified joint 
        ConnectionSet& getJointConnections(std::string jointName);
};

}
}    
#endif
