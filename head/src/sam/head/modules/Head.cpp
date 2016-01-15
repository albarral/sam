/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/head/modules/Head.h"

namespace sam 
{
namespace head
{    
Head::Head ()
{
   address = "";    
   bconnected = false;
   setPanRange(0,0);
   setTiltRange(0,0);   
   bpanLimited = false;
   btiltLimited = false;
}

void Head::setAddress(std::string address)
{
    this->address = address;
}

void Head::setPanRange(int topLeft, int topRight)
{
    minPan = topLeft;
    maxPan = topRight;
}

void Head::setTiltRange(int topDown, int topUp)
{
    minTilt = topDown;        
    maxTilt = topUp;
}

void Head::setPanOffset(int value)
{
    internalPanOffset = value;    
}

void Head::setTiltOffset(int value)
{
    internalTiltOffset = value;
}

void Head::checkLimits()
{
    // pan exceeds min value
    if (limitedPan < minPan)
    {
        limitedPan = minPan;
        bpanLimited = true;
    }
    // pan exceeds max value
    else if (limitedPan > maxPan)
    {
        limitedPan = maxPan;
        bpanLimited = true;
    }
    else
        bpanLimited = false;
       
    // tilt exceeds min value
    if (limitedTilt < minTilt)
    {
        limitedTilt = minTilt;
        btiltLimited = true;
    }
    // tilt exceeds max value
    else if (limitedTilt > maxTilt)
    {
        limitedTilt = maxTilt;
        btiltLimited = true;
    }            
    else
        btiltLimited = false;
}

}
}