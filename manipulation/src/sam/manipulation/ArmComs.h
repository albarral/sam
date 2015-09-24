#ifndef __SAM_ARM_COMS_H
#define __SAM_ARM_COMS_H

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
#include "sam/backbone/AreaConnection.h"
#include "sam/backbone/ControlConnection.h"
//#include "sam/backbone/SensorConnection.h"
#include "sam/network/data/ControlMsg.h"

namespace sam 
{
class ArmComs : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    std::string area;         // sam's area to where this belongs
    // bus
    bool bconnected;        // connected to bus
    manipulation::Bus* pBus;
    // logic
    backbone::AreaConnection oArmAreaConnection;            // connection to backbone's arm components table
    //backbone::ControlConnection oArmControlConnection;   // connection to backbone's arm controls table 
    //backbone::SensorConnection oArmSensorConnection;   // connection to backbone's arm sensors table
    std::map<std::string, int> mapBoneModules;    // map of backbone's arm modules <module_name, module_ID>
    std::map<std::string, int> mapBoneControls;    // map of backbone's arm controls <action_name, action_ID>
    std::map<std::string, int> mapBoneSensors;    // map of backbone's arm sensors <sensor_name, sensor_ID>
    std::vector<std::string> listJointNames;    // list of joints (not a reference to avoid colliding iterations)
    
public:
    ArmComs ();
    ~ArmComs();

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

    // reads & processes new control messages for the arm
    void checkControlMessages();     
    // sends the received control command to the appropriate arm module. Returns true if ok, false if failed.
    bool launchControlAction(network::ControlMsg& oControlMsg);
       
    // send command to ArmMover module
    void send2ArmMover(std::string command, int detail);
    // send command to JointMover module (for specified joint)
    void send2JointMover(std::string command, std::string jointName);
    // send command to JointControl module (for specified joint)
    void send2JointControl(int detail, std::string jointName);
    // send position command directly to joint (for specified joint)
    void send2DirectJoint(int detail, std::string jointName);
    // send position command directly to joint (for specified joint)
    void send2ArmManager(std::string command);

    // Extracts the target joint from the target module string
    std::string getTargetJoint(std::string targetModule);

    // build the modules map with DB info
    void buildModulesMap();
    // build the control and sensor maps with DB info
    void buildControlAndSensorMaps();
    // show modules map in log
    void showModulesMap();
    // show controls map in log
    void showControlsMap();
    // show sensors map in log
    void showSensorsMap();
    
};
}		
#endif
