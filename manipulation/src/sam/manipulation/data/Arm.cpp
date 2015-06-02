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

Joint& Arm::getJointByPos(int pos)
{
    return listJoints.at(pos);
}

Joint& Arm::getJointByName(std::string jointName)
{
    std::vector<Joint>::iterator it_joint = listJoints.begin();
    while (it_joint != listJoints.end())
    {
        if (it_joint->getName().compare(jointName) == 0)
            return *it_joint;
        
        it_joint++;	
    }

    return listJoints.at(0);
}

}
