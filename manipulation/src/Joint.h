#ifndef __SAM_JOINT_H
#define __SAM_JOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam 
{
// Represents an arm's joint
class Joint
{
private:
        bool enabled;
        int ist;        // angle read from encoders (degrees)
        int angle;   // present setpoint angle (degrees)
        int rest;    // angle at which the joint rests (the effort is minimum)
        int type;    // type of joint (moves in pan plane or in tilt plane)
        int length;     // joint's length (cm)
        int limit1;      // lower allowed angle (degrees)
        int limit2;      // upper allowed angle (degrees)

public:
    // joint types
    enum eType
    {
         eJOINT_PAN,   // moves with pan angles (horizontal plane)
         eJOINT_TILT,   // moves with tilt angles (vertical plane)
         eJOINT_INVALID   // none of the others
    };
    
        Joint();
        ~Joint();

        // initializes the joint 
        void init(int type, int length, int limit1, int limit2);        
        
        int getIst() {return ist;};
        void setIst(int value) {ist = value;};
        
        int getAngle() {return angle;};
        void setAngle(int value) {angle = value;};

        int getRestAngle() {return rest;};
        void setRestAngle(int value) {rest = value;};

        int getType() {return type;};
};
}
#endif
