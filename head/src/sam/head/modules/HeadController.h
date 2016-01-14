#ifndef __SAM_HEAD_HEADCONTROLLER_H
#define __SAM_HEAD_HEADCONTROLLER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/utils3/Module.h"
#include "sam/head/modules/Head.h"
#include "sam/head/bus/Bus.h"

namespace sam 
{
namespace head
{    
// This module controls the head motion. 
// It reads pan/tilt commands received through the bus and transmits them to the real head.
// It also delivers the real head position at each moment.
// Controls:
// CO_HEAD_PAN (degrees)
// CO_HEAD_TILT (degrees)   
// Sensors:
// SO_HEAD_PAN (degrees)
// SO_HEAD_TILT (degrees)   
    
class HeadController : public utils::Module
{
public:
    // states of HeadController module
    enum eState
    {
        eSTATE_ON       // just on and off states
    };

private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool bconnected;        // connected to bus
    Bus* pBus;
    // params (none)
    // logic
    Head* pHead;
    bool bmoveRequested;
    // controls & sensors
    bool binhibited;           // module inhibition 
    int reqPan;                 // requested pan 
    int reqTilt;                  // requested tilt      
    int realPan;                // real sensed pan 
    int realTilt;                 // real sensed tilt  

public:
    HeadController();
    
    // initializes the module 
    void init(std::string headModel);   
    // bus connection    
    void connect(Bus& oBus);
       
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
    //void moveHead();
    
    // traces the changes in state
    void showStateName();     
};

}
}
#endif