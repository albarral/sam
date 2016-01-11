#ifndef __SAM_ARM_JOINCOMS_H
#define __SAM_ARM_JOINTCOMS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/manipulation/bus/Bus.h"
#include "sam/network/NetInterpreter.h"
#include "sam/network/data/NetworkCode.h"
#include "sam/network/data/ControlMsg.h"

namespace sam 
{
// Class used for handling joint control messages received from SAM's network.
// Messages are interpreted & the corresponding joint commands are sent to the bus.
class JointComs
{
public:
    enum eJointModules
    {
        eJOINT_POSITION,  
        eJOINT_CONTROL,        
        eJOINT_MOVER                
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string jointName;         // joint for which it responds
    network::NetInterpreter oModuleInterpreter;     // network interpreter for module codes
    network::NetInterpreter oCommandInterpreter;    // network interpreter for control codes         
    goon::ControlT<int>* pCO_JMOVER_ACTION;         // JointMover commands
    goon::ControlT<float>* pCO_JCONTROL_SPEED;    // JointControl commands
    goon::ControlT<float>* pCO_JOINT_ANGLE;           // Direct joint commands

public:
    JointComs ();
    ~JointComs();
    
    // module params
    void init (std::string jointName, manipulation::Bus& oBus);       
    bool isEnabled() {return benabled;};

    void setModuleInterpreter(std::vector<network::NetworkCode>& listAreaComponents);
    void setCommandInterpreter(std::vector<network::NetworkCode>& listAreaComponents);

    // sends the received control command to the appropriate module. Returns true if ok, false if failed.
    bool processMessage(network::ControlMsg& oControlMsg);

private:    
    // send command to JointMover module. Returns true if ok, false otherwise. 
    bool send2JointMover(int networkCommand);
    // send command to JointControl module. Returns true if ok, false otherwise
    bool send2JointControl(float jointSpeed);
    // send position command directly to joint. Returns true if ok, false otherwise 
    bool send2JointPos(float jointAngle);
};
}		
#endif
