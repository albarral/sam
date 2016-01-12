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

}
}