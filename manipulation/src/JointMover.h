#ifndef __SAM_JOINT_MOVER_H
#define __SAM_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam 
{
// Handler that moves a Joint
class JointMover
{
private:
        bool blocked;  // flag to block the joint's movement
        // position info
        int ist;        // angle read from encoders (degrees)
        int angle;   // present setpoint angle (degrees)
        int target;  // final desired joint angle (degrees)
        int rest;    // angle at which the joint rests (the effort is minimum)
        // speed info
        int speed;  // degrees / s
        int maxSpeed;  // maximum speed allowed for the joint
        // configuration info
        int length;     // in cm
        int limit1;      // lower allowed angle (degrees)
        int limit2;      // upper allowed angle (degrees)

public:
        JointMover();
        ~JointMover();

        // initializes the joint 
        void init(int length, int limit1, int limit2, int maxSpeed);        
        // moves the joint towards the target 
        void move();

        // sets the joint speed as a factor of the maxSpeed        
        void setSpeed(float factor);
        void setMaxSpeed(int maxSpeed);
        
        bool isBlocked() {return blocked;};
        
        int getIst() {return ist;};
        int getAngle() {return angle;};
        int getTarget() {return target;};
        int getRest() {return rest;};

        int getSpeed() {return speed;};
        int getMaxSpeed() {return maxSpeed;};
        
        int getLength() {return length;};
        int getLimit1() {return limit1;};
        int getLimit2() {return limit2;};

        void block() {blocked = true;};
        void unblock() {blocked = false;};

        
        void setTarget(int value);
        
        
        
        
        void 
        
        void update(cv::Mat& mat); 
        bool isChanged();
        cv::Mat& getMatNowCopy();
        
private:        
        void checkChanges();        
};
}
#endif
