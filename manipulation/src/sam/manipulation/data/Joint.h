#ifndef __SAM_JOINT_H
#define __SAM_JOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/manipulation/config/ParamsJoint.h"

namespace sam 
{
// Class to represent an arm's joint. To move it use class JointMover.
class Joint
{
private:
    bool benabled;
    // configuration data
    std::string name;
    int rest;    // angle at which the joint rests (the effort is minimum)
    //int type;    // type of joint (moves in pan plane or in tilt plane)
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
    void init(manipulation::ParamsJoint& oParamsJoint);        
    bool isEnabled() {return benabled;};

    std::string getName() {return name;};
    int getRestAngle() {return rest;};
    void setRestAngle(int value) {rest = value;};

    int getLowerLimit() {return limit1;}
    int getUpperLimit() {return limit2;}
    //int getType() {return type;};
};
}
#endif
