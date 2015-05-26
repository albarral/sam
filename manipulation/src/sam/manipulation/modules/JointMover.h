#ifndef __SAM_JOINT_MOVER_H
#define __SAM_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/manipulation/utils/module2.h"
#include "sam/manipulation/bus/ParamsJointMover.h"
#include "sam/manipulation/bus/Bus.h"
#include "goon/utils/Click.h"

namespace sam 
{
// Module that moves a Joint granting a continuous speed value.
// It derives from base class Module2
// It has 4 states:
// STOP    
// move() -> ACCEL    (speed ++)
// brake() -> BRAKE     (speed --)
// keep() -> KEEP        (speed =) 
// stop()-> STOP         (speed 0)
class JointMover : public Module2
{
public:
    // states of JointMover module
    enum eType
    {
         eSTATE_ACCEL, 
         eSTATE_BRAKE, 
         eSTATE_KEEP, 
         eSTATE_STOP
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string jointName;   // module name
    int accel;          // degrees/s2
    int maxSpeed;  // maximum speed allowed for the joint
    int deaccel;          // degrees/s2
    // bus
    bool bconnected;        // connected to bus
    manipulation::Bus* pBus;
    manipulation::ConnectionSet* pConnectionSet;    // the connection set corresponding to its name
    // logic
    int direction;
    float speed;  // output: degrees/s (must be float to grant continuity)
    goon::Click oClick;   
    float accel_ms;    // (degres/s)/ms
    float deaccel_ms;    // (degres/s)/ms

public:
        JointMover();
        //~JointMover();
                
       // module params
       void init (manipulation::ParamsJointMover& oParamsJointMover);       
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(manipulation::Bus& oBus);
       bool isConnected() {return bconnected;};

        int getAccel() {return accel;};
        int getMaxSpeed() {return maxSpeed;};
        int getDeaccel() {return deaccel;};                
        int getDirection() {return direction;};
        float getSpeed() {return speed;};
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // process request received from bus
        void processActionRequest(int reqCommand);
        // write data to bus (speed)
        void writeBus();

        //void setSpeed(int value) {speed = value;};

        // shows the present state name
        void showState();
        // softly increases speed till max value
        bool doAccel();
        // softly reduces speed to 0
        void doBrake();
};
}
#endif