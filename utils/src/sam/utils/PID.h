#ifndef __PID_H
#define __PID_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon 
{
// Utility class for implementing a PID controller.
// Note: for now only PD control is done.    
class PID
{
private:
    float Kp;   // proportional control
    float Ki;   // integral control
    float Kd;   // derivative control
    cv::Vec2f prevInput;    // stores the previous input value
    bool bfirstIteration;     // flag indicating the first iteration of a new control process

public:
    PID();
    
    void setConstants(float kp, float ki, float kd);    
    float getKp() {return Kp;}
    float getKi() {return Ki;}
    float getKd() {return Kd;}
    
    // resets the controller history in order to start a new control process    
    void reset();
    
    // computes & returns the control output regarding the given input.
    cv::Vec2f control(cv::Vec2f input);    
};
}

#endif
