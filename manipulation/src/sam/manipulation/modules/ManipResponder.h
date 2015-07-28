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
#include "sam/manipulation/config/Config.h"
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
    std::map<int, std::string> mapModules;    // map of manipulation modules <symbol_ID, symbol>
    std::map<int, std::string> mapControls;    // map of manipulation control commands <symbol_ID, symbol>
    std::vector<std::string> listJointNames;    // list of joints (not a reference to avoid colliding iterations)
    
public:
    ManipResponder ();
    ~ManipResponder();

    // module params
    void init (manipulation::Config& oConfig);       
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
    // Sends received commands to the appropriate modules. Returns true if ok, false if failed.
    bool processMessage(BoneMsg* pBoneMsg);
       
    // send command to ArmMover module
    void send2ArmMover(std::string info, int detail);
    // send command to JointMover module (for specified joint)
    void send2JointMover(std::string info, int detail, std::string jointName);
    // send command to JointControl module (for specified joint)
    void send2JointControl(std::string info, int detail, std::string jointName);

    // Extracts the target joint from the target module string
    std::string getTargetJoint(std::string targetModule);

    // build the modules map with DB info
    void buildModulesMap();
    // build the controls map with DB info
    void buildControlsMap();
    // show modules map in log
    void showModulesMap();
    // show controls map in log
    void showControlsMap();
};
}		
#endif
