#ifndef __SAM_COMS_MANIP_H
#define __SAM_COMS_MANIP_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "sam/manipulation/bus/Bus.h"
#include "sam/manipulation/config/Config.h"
#include <sam/manipulation/utils/Responder.h>
#include <sam/utils/module2.h>
#include "Commands.h"

namespace sam 
{
class ComsManip : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    manipulation::Bus* pBus;
    // logic
    std::vector<std::string> listJointNames;
    manipulation::Commands oCommands;
    Responder oResponder;    
    std::string activeJointName;    // name of controlled joint
    

public:
    ComsManip ();
    ~ComsManip();

    // module params
    void init (manipulation::Config& oConfig);       
    bool isEnabled() {return benabled;};

    // bus connection 
    void connect(manipulation::Bus& oBus);
    bool isConnected() {return bconnected;};
    
    // ask the module to stop
    void stop();
        
private:
    void first();
    // executes the behaviour
    void loop ();

    // performs a request to the arm mover module
    void sendArmMoverCommand(int reqCommand);    
    
    // performs a request to the individual joint modules
    void sendJointCommand(int reqCommand);    
    
    // directly requests an angle position
    void sendJointAngle(int angleCommand);    
    
    void showResponderWords();
};
}		
#endif
