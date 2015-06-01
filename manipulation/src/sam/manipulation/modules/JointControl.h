#ifndef __SAM_JOINT_CONTROL_H
#define __SAM_JOINT_CONTROL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/manipulation/utils/module2.h"
#include "sam/manipulation/bus/ConnectionsJoint.h"
#include "sam/manipulation/data/Joint.h"
#include "goon/utils/Click.h"

namespace sam 
{
// Module that sets a Joint's angle given a commanded speed value.
// It derives from base class Module2
class JointControl : public Module2
{
public:
    // states of JointControl module
    enum eState
    {
         eSTATE_GO
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string name;   // module name
    Joint* mJoint;        // controlled joint  
    // bus
    bool bconnected;        // connected to bus
    manipulation::ConnectionsJoint* pConnectionsJoint;    // the bus connections corresponding to a given joint
    // logic
    float reqSpeed;     // requested speed
    float angle;            // output: degrees (must be float to grant continuity)
    goon::Click oClick;   
    float speed_ms;     // requested speed (deg/ms))
    int limitBroken;    // commanded angle out of joint's range  

public:
        JointControl();
        //~JointControl();
                
       // module params
       void init (std::string name, Joint& oJoint);       
       bool isEnabled() {return benabled;};

       // bus connection               
       void connect(manipulation::ConnectionsJoint& oConnectionsJoint);              
       bool isConnected() {return bconnected;};

        Joint* getJoint() {return mJoint;};
        float getAngle() {return angle;};
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();
        // translate commanded speed into next joint angle
        void doSpeed2Angle();
};
}
#endif
