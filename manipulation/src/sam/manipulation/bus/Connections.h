#ifndef __SAM_MANIPULATION_CONNECTIONS_H
#define __SAM_MANIPULATION_CONNECTIONS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/manipulation/data/defines.h"
#include "sam/manipulation/bus/ConnectionsJoint.h"

namespace sam 
{
namespace manipulation 
{    
class Connections
{
    private:        
        bool benabled;
        ConnectionsJoint oConnectionsJoint[SAM_MAX_JOINTS];
        int numJoints;   // number of active joints
        
    public:
        Connections();
        //~Connections();

        // initializes a ConnectionsJoint object for the given joint name. Returns true if ok, false otherwise.
        bool add4Joint(std::string jointName);
        bool isEnabled() {return benabled;};
        
        // gets the connections set for the specified joint 
        ConnectionsJoint& getConnectionsJoint(std::string jointName);
        
      
private:
    // checks if the given joint name is already used
    bool checkExistingJoint(std::string jointName);
};

}
}    
#endif
