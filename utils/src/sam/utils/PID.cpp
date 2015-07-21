/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "PID.h"

using namespace std;

namespace goon 
{
PID::PID()
{
    Kp = Ki = Kd = 0;
    bfirstIteration = true;
}

void PID::setConstants(float kp, float ki, float kd)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
}

void PID::reset()
{    
    bfirstIteration = true;
    prevInput = 0;
}

cv::Vec2f PID::control(cv::Vec2f input)
{
    cv::Vec2f output;
    
    if (!bfirstIteration)
    {
        output = Kp*input + Kd*(input - prevInput);     // PD control
    }
    // on first iteration there's no input history
    else
    {
        output = Kp*input;      //  simple P control
        bfirstIteration = false;
    }
    // store input for next computation of derivative term
    prevInput = input;                
    return output;    
}
}