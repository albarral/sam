#ifndef __SAM_JOINT_MOVER_H
#define __SAM_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/manipulation/utils/module2.h"
#include "sam/manipulation/data/Joint.h"

namespace sam 
{
// Module that moves a Joint by speed commands.
// It derives from base class sam::Module2
// It has 4 states:
// STOP    
// launch() -> ACCEL    (speed ++)
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
    Joint& mJoint;    
    int accel;          // degrees/s2
    int maxSpeed;  // maximum speed allowed for the joint
    int deaccel;          // degrees/s2
    int direction;
    int speed;  // degrees / s

public:
        JointMover(Joint& oJoint);
        //~JointMover();
                
       void setParams (int accel, int max_speed, int deaccel);
        
        // starts movement (in the specified joint direction)
        void move(int direction);
        // starts braking until the joint stops
        void brake();
        // keeps the present speed
        void keep();
        // suddenly stops the joint
        void stop();        
        
        Joint& getJoint() {return mJoint;};

        int getAccel() {return accel;};
        int getMaxSpeed() {return maxSpeed;};
        int getDeaccel() {return deaccel;};
                
        int getDirection() {return direction;};
        int getSpeed() {return speed;};
        
private:       
        void setSpeed(int value) {speed = value;};

        // initialization when the module thread begins
        virtual void init();
        // loop inside the module thread 
        virtual void loop();            

};
}
#endif
