#ifndef __SAM_ARM_MOVER_H
#define __SAM_ARM_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/manipulation/utils/module2.h"
#include "sam/manipulation/bus/Connections.h"
#include "goon/utils/Click.h"

namespace sam 
{
// Module that performs a cyclic horizontal arm movement
// It derives from base class Module2
// It has 5 states:
// WAIT
// RIGHT
// CHANGE
// LEFT
// STOP
class ArmMover : public Module2
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,
         eSTATE_RIGHT, 
         eSTATE_CHANGE, 
         eSTATE_LEFT,
         eSTATE_STOP
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int timeChange;     // milliseconds
    // bus
    bool bconnected;        // connected to bus
    manipulation::Connections* pConnections;    // the bus connections
    // logic
    float realSpeed;
    int prevState;
    goon::Click oClick;   

public:
        ArmMover();
        //~ArmMover();
                
       // module params
       void init (int timeChange);
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(manipulation::Connections& oConnections);
       bool isConnected() {return bconnected;};
       
       void start();
       void stop();
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write action commands to bus
        void writeBus(int command);

        // shows the present state name
        void showState();
};
}
#endif
