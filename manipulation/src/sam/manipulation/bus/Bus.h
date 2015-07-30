#ifndef __SAM_MANIPULATION_BUS_H
#define __SAM_MANIPULATION_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/manipulation/config/defines.h"
#include "sam/manipulation/bus/ConnectionsJoint.h"
#include "sam/utils/brooks/control.h"

namespace sam 
{
namespace manipulation 
{    
class Bus
{
    private:        
        bool benabled;
        
        // CONTROLS (receiver modules)
        // ArmManager
        goon::Control CO_FINISH_MANAGER;    // finish all modules 
        // ArmMover 
        goon::Control CO_ARMMOVER_START;       // ArmMover command: start 
        goon::Control CO_ARMMOVER_STOP;       // ArmMover command: stop
        
        // connections for individual joints 
        ConnectionsJoint oConnectionsJoint[SAM_MAX_JOINTS];
        int numJoints;   // number of active joints
        
    public:
        Bus();
        //~Connections();

        // initializes a ConnectionsJoint object for the given joint name. Returns true if ok, false otherwise.
        bool add4Joint(std::string jointName);
        bool isEnabled() {return benabled;};
        
        // controls
        goon::Control& getCO_FINISH_MANAGER() {return CO_FINISH_MANAGER;};   
        goon::Control& getCO_ARMMOVER_START() {return CO_ARMMOVER_START;};        
        goon::Control& getCO_ARMMOVER_STOP() {return CO_ARMMOVER_STOP;};        
        
        // gets the connections set for the specified joint name
        ConnectionsJoint& getConnectionsJoint(std::string jointName);
        // gets the connections set for the specified joint index        
        ConnectionsJoint& getConnectionsJointByIndex(int index);
        
      
private:
    // checks if the given joint name is already used
    bool checkExistingJoint(std::string jointName);
};

}
}    
#endif
