#ifndef __SAM_MANIPULATION_CONNECTIONS_JOINT_H
#define __SAM_MANIPULATION_CONNECTIONS_JOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/utils/brooks/controlT.h"
#include "sam/utils/brooks/sensorT.h"

namespace sam 
{
namespace manipulation 
{    
// Set of bus connections for a specific joint. 
// All modules controlling this joint must be connected through this bus section.
class ConnectionsJoint
{
    private:        
        bool benabled;
        std::string jointName;
        // JointMover module
        goon::ControlT<int> coAction;       // move actions: move, brake, keep, stop
        goon::ControlT<float> coSpeed;    // desired joint speed (degrees/s)
        // JointControl module
        goon::SensorT<float> soRealSpeed;     // real joint speed (degrees/s)
        goon::SensorT<int> soLimitReached;     // range limit reached: 0, 1 (top limit), -1 (bottom limit)
        goon::ControlT<float> coAngle;         // desired joint angle (degrees)
        // external sensing
        goon::SensorT<float> soIst;            // real joint angle (degrees)
        
    public:
        ConnectionsJoint();
        //~ConnectionsJoint();
                
        // initializes the class with the given joint name
        void init (std::string jointName);        
        bool isEnabled() {return benabled;};
        std::string& getJointName() {return jointName;};

        // JointMover module
        goon::ControlT<int>& getCOAction() {return coAction;};        
        goon::ControlT<float>& getCOSpeed() {return coSpeed;};                
        
        // JointControl module
        goon::SensorT<float>& getSORealSpeed() {return soRealSpeed;}; 
        goon::SensorT<int>& getSOLimitReached() {return soLimitReached;}; 
        goon::ControlT<float>& getCOAngle() {return coAngle;};                

        // external sensing
        goon::SensorT<float>& getSOIst() {return soIst;}; 
};

}
}    
#endif
