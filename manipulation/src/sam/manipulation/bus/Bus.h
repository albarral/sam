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
        // general commands
        goon::Control coFinish;    // finish all modules 
        // ArmMover module
        goon::Control coArmMoverStart;       // ArmMover command: start 
        goon::Control coArmMoverStop;       // ArmMover command: stop
        // modules for individual joints 
        ConnectionsJoint oConnectionsJoint[SAM_MAX_JOINTS];
        int numJoints;   // number of active joints
        
    public:
        Bus();
        //~Connections();

        // initializes a ConnectionsJoint object for the given joint name. Returns true if ok, false otherwise.
        bool add4Joint(std::string jointName);
        bool isEnabled() {return benabled;};
        
        goon::Control& getCOFinish() {return coFinish;};   
        
        // ArmMover module
        goon::Control& getCOArmMoverStart() {return coArmMoverStart;};        
        goon::Control& getCOArmMoverStop() {return coArmMoverStop;};        
        
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
