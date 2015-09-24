/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range
#include "log4cxx/ndc.h"

#include "ArmComs.h"
#include "sam/manipulation/modules/JointMover.h"
#include "sam/backbone/config/Config.h"
#include "sam/backbone/data/BoneModule.h"
#include "sam/backbone/data/BoneComponent.h"


using namespace log4cxx;

namespace sam
{
LoggerPtr ArmComs::logger(Logger::getLogger("sam.manipulation"));

// Constructor 
ArmComs::ArmComs ()
{           
    benabled = false;
    area = "manipulation";
 }

// Destructor
ArmComs::~ArmComs ()
{
    mapModules.clear();
}

void ArmComs::init (manipulation::Config& oConfig)
{
    LOG4CXX_INFO(logger, "ArmComs: init");          
    
    // list of joints
    listJointNames = oConfig.getListJointNames();
    
    // sets connections to the backbone's centers for the arm (controls & sensors)
    backbone::Config oBoneConfig;
    oArmControlConnection.init(oBoneConfig);
    oArmControlConnection.tune2Table(oBoneConfig.getTabArmControl());
    //oArmSensorConnection.init(oBoneConfig);
    //oArmSensorConnection.tune2Table(oBoneConfig.getTabArmSense());
        
    if (oArmControlConnection.isInitialized() && oArmControlConnection.isTuned())
    {
        buildModulesMap();
        buildControlAndSensorMaps();
        benabled = true;    
        LOG4CXX_INFO(logger, "ArmComs: initialized ok");          
        showModulesMap();
        showControlsMap();        
        showSensorsMap();        
    }
    else
        LOG4CXX_ERROR(logger, "ArmComs: failed to initialize!");              
};

void ArmComs::connect(manipulation::Bus& oBus)
{
    pBus = &oBus;
    bconnected = true;

    LOG4CXX_INFO(logger, "ArmComs connected to bus");      
}

void ArmComs::first()
{    
    log4cxx::NDC::push("ArmComs");   	
}

void ArmComs::loop()
{
    LOG4CXX_INFO(logger, "> process new messages");    
    checkControlMessages();      
}


void ArmComs::checkControlMessages()
{    
    bool bprocessedOK;
    
    // read messages from DB
    oArmControlConnection.readMessages();
    
    // skip if no messages received
    if (oArmControlConnection.getNumReadMessages() == 0)
        return;
    
    LOG4CXX_INFO(logger, "Messages read = " + oArmControlConnection.getNumReadMessages());    
    
    std::vector<backbone::ControlMsg>::iterator it_control = oArmControlConnection.getListMessages().begin();
    std::vector<backbone::ControlMsg>::iterator it_end = oArmControlConnection.getListMessages().end();
    
    // process each control message one by one
    while (it_control != it_end)
    {
        // send the appropriate control action to the corresponding module
        bprocessedOK = launchControlAction(*it_control);
        
        // then mark message as processed or failed
        if (bprocessedOK)
            oArmControlConnection.markMessageOk(it_control->getModuleID());
        else
            oArmControlConnection.markMessageFailed(it_control->getModuleID());
        
        it_control++;
    }
 }

bool ArmComs::launchControlAction(backbone::ControlMsg& oControlMsg)
{
    std::string targetModule;       // a module symbol
    std::string targetJoint;            // a joint name 
    std::string command;   // a control symbol

    LOG4CXX_INFO(logger, "Process message " + oControlMsg.toString());    

    // obtain target module for the received message
    try
    {
        targetModule = mapModules.at(oControlMsg.getModuleID());
        command = mapControls.at(oControlMsg.getActionID());
    }
    catch (std::out_of_range)
    {
        LOG4CXX_ERROR(logger, "Invalid message! Module or command not supported - " << oControlMsg.toString());
        return false;
    }
        
   // deliver command to the appropriate module ... 
   LOG4CXX_INFO(logger, "Target module: " + targetModule);    
   
   // command for ARMMOVER module
   if (targetModule.compare("ARMMOV") == 0)
   {
       send2ArmMover(command, oControlMsg.getDetail());
   }
   // command for JOINTMOVER module
   else if (targetModule.find("MOV") != std::string::npos)
   {
       // obtain the target joint from the module symbol
       targetJoint = getTargetJoint(targetModule);
       
       send2JointMover(command, targetJoint);
   }
   // command for JOINTCONTROL module
   else if (targetModule.find("CON") != std::string::npos)
   {
       // obtain the target joint from the module symbol
       targetJoint = getTargetJoint(targetModule);
       
       send2JointControl(oControlMsg.getDetail(), targetJoint);
   }
   // command for JOINT angle
   else if (targetModule.find("POS") != std::string::npos)
   {
       // obtain the target joint from the module symbol
       targetJoint = getTargetJoint(targetModule);
       
       send2DirectJoint(oControlMsg.getDetail(), targetJoint);
   }
   // command for MANIPULATION area
   else if (targetModule.compare("AMANIP") == 0)
   {
       send2ArmManager(command);
   }
   else 
   {
       LOG4CXX_WARN(logger, "Invalid target module! Message ignored ... " << oControlMsg.toString());
       return false;
   }
          
   return true;
}

// Commands for ArmMover module
void ArmComs::send2ArmMover(std::string command, int detail)
{    
    LOG4CXX_INFO(logger, "> ArmMover - " << command);    

    // CO start
    if (command.compare("START") == 0)
    {
        pBus->getCO_ARMMOVER_START().request(); 
    }
    // CO stop
    else if (command.compare("STOP") == 0)
    {
        pBus->getCO_ARMMOVER_STOP().request();            
    }
    else
        LOG4CXX_WARN(logger, "> unknown command!");
}


void ArmComs::send2JointMover(std::string command, std::string jointName)
{    
    int moverAction = -1;

    LOG4CXX_INFO(logger, "> JointMover " << jointName << " - " << command);    
    
    // send proper JointMover action
    if (command.compare("MOVPOS") == 0)
    {
        moverAction = JointMover::eMOV_POSITIVE;
    }
    else if (command.compare("MOVNEG") == 0)
    {
        moverAction = JointMover::eMOV_NEGATIVE;
    }
    else if (command.compare("MOVBRA") == 0)
    {
        moverAction = JointMover::eMOV_BRAKE;
    }
    else if (command.compare("STOP") == 0)
    {
        moverAction = JointMover::eMOV_STOP;
    }
    
    // write CO_MOVE_ACTION
    if (moverAction >=0 )        
        pBus->getConnectionsJoint(jointName).getCO_JMOVER_ACTION().request(moverAction);            
    else
        LOG4CXX_WARN(logger, "> unknown command!");
}


void ArmComs::send2JointControl(int detail, std::string jointName)
{
    LOG4CXX_INFO(logger, "> JointControl " << jointName << " - speed = " << detail);    

    // WRITE CO_SOLL_SPEED
    float speed = detail;
    pBus->getConnectionsJoint(jointName).getCO_JCONTROL_SPEED().request(speed);
}


void ArmComs::send2DirectJoint(int detail, std::string jointName)
{
    LOG4CXX_INFO(logger, "> Joint " << jointName << " - angle = " << detail);    

    // WRITE CO_SOLL_ANGLE
    float angle = detail;
    pBus->getConnectionsJoint(jointName).getCO_JOINT_ANGLE().request(angle);
}


// Commands for ArmManager area
void ArmComs::send2ArmManager(std::string command)
{    
    LOG4CXX_INFO(logger, "> ArmManager - " << command);    

    // CO start
    if (command.compare("FINISH") == 0)
    {
        pBus->getCO_FINISH_MANAGER().request(); 
    }
    else
        LOG4CXX_WARN(logger, "> unknown command!");
}

// extracts the joint name from the target module symbol
std::string ArmComs::getTargetJoint(std::string moduleSymbol)
{
    // extract the joint number from the module symbol
    std::string jointText = moduleSymbol.substr(1, 1);       // J1_MOV, J2_CON, ...
    int jointNum = std::stoi(jointText);
    
    // joint 1 is at position 0 ...
    std::string jointName = listJointNames.at(jointNum-1);
    
    return jointName;
}

void ArmComs::buildModulesMap()
{
    LOG4CXX_INFO(logger, "Building modules map ...");
    
   // creates a map with the list of supported modules for arm's control
    std::vector<backbone::BoneModule> listArmModules; //= oBoneReader.readAreaModules();
    
    for (backbone::BoneModule& oBoneModule : listArmModules)
    {
        mapModules.emplace(oBoneModule.getID(), oBoneModule.getName());        
    }        
}

void ArmComs::buildControlAndSensorMaps()
{
    LOG4CXX_INFO(logger, "Building control & sensor maps ...");

    // creates a map with the list of supported actions for arm's control
    std::vector<backbone::BoneItem> listArmItems; // = oBoneReader.readAreaControls();
    
    for (backbone::BoneItem& oBoneItem : listArmItems)
    {
        if (oBoneItem.isActionItem())
            mapControls.emplace(oBoneItem.getID(), oBoneItem.getName());     
        else if (oBoneItem.isSensorItem())
            mapSensors.emplace(oBoneItem.getID(), oBoneItem.getName());     
    }        
}

void ArmComs::showModulesMap()
{
    LOG4CXX_INFO(logger, "ArmComs modules map:");      
     for (auto& element : mapModules) 
     {
        LOG4CXX_INFO(logger, element.first << ": " << element.second);      
    }    
}

void ArmComs::showControlsMap()
{
    LOG4CXX_INFO(logger, "ArmComs controls map:");      
     for (auto& element : mapControls) 
     {
        LOG4CXX_INFO(logger, element.first << ": " << element.second);      
    }    
}

void ArmComs::showSensorsMap()
{
    LOG4CXX_INFO(logger, "ArmComs sensors map:");      
     for (auto& element : mapSensors) 
     {
        LOG4CXX_INFO(logger, element.first << ": " << element.second);      
    }    
}

}