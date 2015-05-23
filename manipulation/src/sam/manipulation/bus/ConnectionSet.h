#ifndef __SAM_MANIPULATION_CONNECTIONSET_H
#define __SAM_MANIPULATION_CONNECTIONSET_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/utils/brooks/controlT.h"
#include "goon/utils/brooks/sensorT.h"

namespace sam 
{
namespace manipulation 
{    
class ConnectionSet
{
    private:        
        // JointMover module
        goon::ControlT<int> coAction;        // move, brake, keep, stop
        goon::ControlT<float> coSpeed;        
        // JointControl module
        goon::SensorT<float> soRealSpeed;     
        goon::SensorT<int> soLimitReached;     // 0, 1 (top limit reached), -1 (bottom limit reached)
        goon::ControlT<int> coAngle;         // commanded joint angle
        // external sensing
        goon::SensorT<int> soIst;            // sensed joint angle
        
    public:
        ConnectionSet();
        //~ConnectionSet();
                
        // JointMover module
        goon::ControlT<int>& getCOAction() {return coAction;};        
        goon::ControlT<float>& getCOSpeed() {return coSpeed;};                
        
        // JointControl module
        goon::SensorT<float>& getSORealSpeed() {return soRealSpeed;}; 
        goon::SensorT<int>& getSOLimitReached() {return soLimitReached;}; 
        goon::ControlT<int>& getCOAngle() {return coAngle;};                

        // external sensing
        goon::SensorT<int>& getSOIst() {return soIst;}; 
};

}
}    
#endif
