/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

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
    if (pos < listJoints.size())
        return listJoints.at(pos);
    else 
        return 0; //NULL;
}

}
