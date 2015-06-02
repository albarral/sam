#ifndef __SAM_ARM_H
#define __SAM_ARM_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/manipulation/data/Joint.h"

namespace sam 
{
// Class to represent an arm as list of joints. 
class Arm
{
private:
    bool benabled;
    std::vector<Joint> listJoints;
   
public:    
    Arm();
    ~Arm();

    bool isEnabled() {return benabled;};
    
    // reset joints
    void reset();
    // add a new joint
    void addJoint(Joint& oJoint);
    // get joints list
    std::vector<Joint>& getListJoints() {return listJoints;};
    // gets number of joints
    int getNumJoints() {return listJoints.size();};
    
    // get specific joint by position
    Joint& getJointByPos(int pos);
    // get specific joint by name
    Joint& getJointByName(std::string jointName);
    
};
}
#endif
