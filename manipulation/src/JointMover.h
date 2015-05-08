#ifndef __SAM_JOINT_MOVER_H
#define __SAM_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Joint.h"

namespace sam 
{
// Handler that moves a Joint
class JointMover
{
protected:
    bool benabled;
    Joint& mJoint;    
    int start;    // initial position of a joint movement (degrees)
    int target;  // desired final position of a joint movement (degrees)
    int speed;  // degrees / s
    // configuration data
    int tolerance; // allowed tolerance for target reaching (degrees))
    int maxSpeed;  // maximum speed allowed for the joint
    int accel;          // degrees/s2
    bool blocked;  // flag to block the joint's movement

public:
        JointMover(Joint& oJoint);
        //~JointMover();
                
       void init (int tolerance, int max_speed, int accel);
        
        bool isEnabled() {return benabled;};

       // sets a new target for the joint 
        virtual void setTarget(int value);
        // moves the joint towards the target 
        virtual void move() = 0;
        // sets as target the rest angle
        void rest();
        
        
        Joint& getJoint() {return mJoint;};
        int getTarget() {return target;};

        int getSpeed() {return speed;};
        void setSpeed(int value) {speed = value;};

        int getMaxSpeed() {return maxSpeed;};
        void setMaxSpeed(int value) {maxSpeed = value;};
                
        int getAccel() {return accel;};
        void setAccel(int value) {accel = value;};
        
        // block handling        
        bool isBlocked() {return blocked;};
        void block() {blocked = true;};
        void unblock() {blocked = false;};
};
}
#endif
