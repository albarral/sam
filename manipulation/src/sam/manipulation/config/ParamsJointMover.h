#ifndef __SAM_MANIPULATION_PARAMSJOINTMOVER_H
#define __SAM_MANIPULATION_PARAMSJOINTMOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace manipulation 
{
// Config params for JointMover modules
class ParamsJointMover 
{
    private:                
        std::string jointName;
        int accel;          // degrees/s2
        int maxSpeed;  // maximum speed allowed for the joint
        int deaccel;      // degrees/s2
        
    public:
        ParamsJointMover();

        void set(std::string jointName, int accel, int maxSpeed, int deaccel) {this->jointName = jointName; this->accel = accel; this->maxSpeed = maxSpeed; this->deaccel = deaccel;}

        std::string& getJointName() {return jointName;};
        int getAccel() {return accel;}
        int getMaxSpeed() {return maxSpeed;}
        int getDeaccel() {return deaccel;}
};

}
}    
#endif
