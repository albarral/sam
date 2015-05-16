/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "JointMover.h"

namespace sam 
{
JointMover::JointMover(Joint& oJoint) : mJoint(oJoint)
{
    benabled = false;
}

//JointMover::~JointMover()
//{
//}

void JointMover::init(int tolerance, int max_speed, int accel)
{
    // control proper argument values
    if (tolerance < 0 || 
       max_speed < 0 ||
       accel < 0)
        return;

    this->tolerance = tolerance;
    this->maxSpeed = max_speed;
    this->accel = accel;
    benabled = true;
};

        
void JointMover::setTarget(int value)
{
    if (benabled)
    {
        target = value;
        start = mJoint.ist;
    }
}

void JointMover::rest()
{
    setTarget(mJoint.getRestAngle());    
}
}
