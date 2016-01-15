#ifndef __SAM_LOOK_TRACKER_H
#define __SAM_LOOK_TRACKER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/utils3/Module.h"
#include "sam/utils3/Click.h"
#include "sam/look/bus/Bus.h"
#include "sam/network2/NetworkUser.h"

namespace sam 
{
namespace look
{    
// Module in charge of tracking a focused object. TO EXTEND ...
// Connections: internal bus & SAM's network.    
class Tracker : public utils::Module, public network::NetworkUser
{
public:
    // states of Tracker module
    enum eState
    {
        eSTATE_START,      // start tracking a new target 
        eSTATE_TRACK,      // move head following the target (trying to emulate the target speed)
        eSTATE_LOST         // target is lost, no head moves    
    };

private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool busConnected;        // connected to bus
    Bus* pBus;
    // params (none)
    // logic
    int panSpeed;        // degrees/sec   
    int tiltSpeed;          // degrees/sec        
    utils::Click oClick;   
    int counterPan;
    int counterTilt;
    // controls & sensors
    bool binhibited;           // module inhibition 
    int realPan;           // real sensed pan
    int realTilt;            // real sensed tilt
    float reqPan;              // requested pan (must be float to accumulate small increments)
    float reqTilt;               // requested tilt  (must be float to accumulate small increments)    
    int headPriority;          // priority for head control

public:
    Tracker();
    
    // initializes the module 
    void init();   
    // bus connection    
    void busConnect(Bus& oBus);
       
private:
    // first action after thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    
    // moves the head to the commanded position
    void followTarget();
    
    // TEST method: when pan/tilt limits are reached, speed sign is changed
    void switchSpeedOnLimit();
    
    // traces the changes in state
    void showStateName();     
};

}
}
#endif
