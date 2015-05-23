/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <stddef.h>

#include "Arm.h"

namespace sam 
{
Arm::Arm ()
{
    benabled = false;
}

Arm::~Arm()
{
    reset();
}

void Arm::reset()
{
    listJoints.clear();    
}

void Arm::addJoint(Joint& oJoint)
{
    listJoints.push_back(oJoint);    
    benabled = true;
}

Joint& Arm::getJoint(int pos)
{
    return listJoints.at(pos);
}

}
