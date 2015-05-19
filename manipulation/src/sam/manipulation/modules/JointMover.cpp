/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "JointMover.h"

namespace sam 
{
JointMover::JointMover(Joint& oJoint) : mJoint(oJoint)
{
    accel = 0;
    maxSpeed = 0;
    deaccel = 0;
    direction = 0;
    speed = 0;
}

//JointMover::~JointMover()
//{
//}

void JointMover::setParams(int accel, int max_speed, int deaccel)
{
    // control proper argument values
    if (accel < 0 || 
       max_speed < 0 ||
       deaccel < 0)
        return;

    this->accel = accel;
    this->maxSpeed = max_speed;
    this->deaccel = deaccel;
};


void JointMover::init()
{
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);
}
    
// starts movement (in the specified joint direction)
void JointMover::move(int direction)
{
    setNextState(eSTATE_ACCEL);
}
    
// starts braking until the joint stops        
void JointMover::brake()
{
    setNextState(eSTATE_BRAKE);    
}
        
// keeps the present speed
void JointMover::keep()
{
    setNextState(eSTATE_KEEP);    
}

// suddenly stops the joint
void JointMover::stop()
{
    setNextState(eSTATE_STOP);    
}
        
        
void JointMover::loop()
{
    updateState();
      
    switch (getState())
    {
        case eSTATE_ACCEL:
            // waits till board changes, then jums to CHANGING

            if (checkBoardChanged())
            {
                changeState(eFIELD_CHANGING); 
            }
            break;
            
        case eSTATE_BRAKE:
            // waits till changes finished, then raises board changed flag & jums to CHANGED
            
            if (!checkBoardChanged())
            {
                mConnections.getSOBoardChanged().setValue(true);
                changeState(eFIELD_CHANGED);
            }
            break;
                    
        case eSTATE_KEEP:
            // waits till ack is received, then lowers board changed flag & jumps to STATIC
            // if new changes happen, goes back to CHANGING

            if (checkBoardChanged())
            {
                changeState(eFIELD_CHANGING); 
            }
            // ack received -> STATIC & lower "board changed" flag
            else if (mConnections.getCOAckBoardChanged().isRequested())                
            {
                mConnections.getSOBoardChanged().setValue(false);
                changeState(eFIELD_STATIC); 
            }
            break;
            
        case eSTATE_STOP:
            
            // TO DO ...
            break;
    }   // end switch    
}
