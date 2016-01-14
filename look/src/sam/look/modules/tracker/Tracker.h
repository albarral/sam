#ifndef __SAM_LOOK_TRACKER_H
#define __SAM_LOOK_TRACKER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/utils3/Module.h"
#include "sam/look/bus/Bus.h"
#include "sam/network2/Network.h"

namespace sam 
{
namespace look
{    
// to fill ...    
class Tracker : public utils::Module
{
public:
    // states of Tracker module
    enum eState
    {
        eSTATE_ON       // just on and off states
    };

private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool bconnected;        // connected to bus
    Bus* pBus;
    network::Network* pNetwork;     // sam's network
    // params (none)
    // logic
    // controls & sensors
    bool binhibited;           // module inhibition 
    int reqPan;                 // requested pan 
    int reqTilt;                  // requested tilt      

public:
    Tracker();
    
    // initializes the module 
    void init();   
    // bus connection    
    void connect(Bus& oBus, network::Network* pNetwork);
       
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
    void sendMove();
    
    // traces the changes in state
    void showStateName();     
};

}
}
#endif
