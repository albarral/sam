#ifndef __SAM_MANIP_RESPONDER_H
#define __SAM_MANIP_RESPONDER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <map>
#include <string>
#include <log4cxx/logger.h>

#include <sam/utils/module2.h>
#include "sam/manipulation/bus/Bus.h"
#include "sam/backbone/BoneReader.h"

namespace sam 
{
class ManipResponder : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string area;         // sam's area to where this belongs
    // bus
    bool bconnected;        // connected to bus
    manipulation::Bus* pBus;
    // logic
    BoneReader oBoneReader;
    std::map<int, std::string> mapModules;    

public:
    ManipResponder ();
    ~ManipResponder();

    // module params
    void init ();       
    bool isEnabled() {return benabled;};

    // bus connection 
    void connect(manipulation::Bus& oBus);
    bool isConnected() {return bconnected;};
            
private:
    void first();
    // executes the behaviour
    void loop ();

    // reads & processes new backbone messages
    void check4NewMessages();     
    // Transfers message command to the manipulation bus. Returns true if ok, false if failed.
    bool processMessage(BoneMsg* pBoneMsg);
    
    // send command to ArmMover module
    void sendArmMover(std::string info, int detail);
    // send command to JointMover module (for specified joint)
    void sendJointMover(std::string info, int detail, std::string jointName);
    // send command to JointControl module (for specified joint)
    void sendJointControl(std::string info, int detail, std::string jointName);
    
    // build a map with module IDs and their name
    void buildModulesMap();
    // shows map in log
    void showModulesMap();
};
}		
#endif
