/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range
#include "log4cxx/ndc.h"

#include "ManipResponder.h"
#include "sam/backbone/data/BoneModul.h"
#include "sam/backbone/data/BoneMsg.h"
#include "sam/manipulation/modules/JointMover.h"

using namespace log4cxx;

namespace sam
{
LoggerPtr ManipResponder::logger(Logger::getLogger("sam.manipulation"));

// Constructor 
ManipResponder::ManipResponder ()
{           
    benabled = false;
    area = "manipulation";
 }

// Destructor
ManipResponder::~ManipResponder ()
{
    mapModules.clear();
}

void ManipResponder::init (manipulation::Config& oConfig)
{
    LOG4CXX_INFO(logger, "ManipResponder: init");          
    
    // list of joints
    listJointNames = oConfig.getListJointNames();
    
    // connect the backbone reader & tune it to the control table
    oBoneReader.init();
    oBoneReader.tune(BoneBase::eTAB_CONTROL, area);
    
    // if connected, create the modules map (for interpreting the received messages)
    if (oBoneReader.isReady())
    {
        buildModulesMap();
        buildControlsMap();
        benabled = true;    
        LOG4CXX_INFO(logger, "ManipResponder: initialized ok");          
        showModulesMap();
        showControlsMap();
    }
    else
        LOG4CXX_ERROR(logger, "ManipResponder: failed to initialize!");              
};

void ManipResponder::connect(manipulation::Bus& oBus)
{
    pBus = &oBus;
    bconnected = true;

    LOG4CXX_INFO(logger, "ManipResponder connected to bus");      
}

void ManipResponder::first()
{    
    log4cxx::NDC::push("ManipResponder");   	
}

void ManipResponder::loop()
{
    LOG4CXX_INFO(logger, "> process new messages");    
    processNewMessages();      
}


void ManipResponder::processNewMessages()
{
    BoneMsg* pBoneMsg = 0;

    // read messages from DB
    oBoneReader.readMessages();

    // skip if no messages received
    if (oBoneReader.getNumReadMessages() == 0)
        return;
    
    LOG4CXX_INFO(logger, "Messages read = " + oBoneReader.getNumReadMessages());    
    
    // process them one by one
    while (oBoneReader.nextMessage())
    {
        pBoneMsg = oBoneReader.getMessage();    
        
        // mark them as processed or failed
        if (processMessage(pBoneMsg))
            oBoneReader.markMessageOk(pBoneMsg->getModule());
        else
            oBoneReader.markMessageFailed(pBoneMsg->getModule());
    }    
}

bool ManipResponder::processMessage(BoneMsg* pBoneMsg)
{
    std::string targetModule;       // a module symbol
    std::string targetJoint;            // a joint name 
    std::string command;   // a control symbol

    LOG4CXX_INFO(logger, "Process message " + pBoneMsg->toString());    

    // obtain target module for the received message
    try
    {
        targetModule = mapModules.at(pBoneMsg->getModule());
        command = mapControls.at(pBoneMsg->getInfo());
    }
    catch (std::out_of_range)
    {
        LOG4CXX_ERROR(logger, "Invalid message! Module or command not supported - " << pBoneMsg->toString());
        return false;
    }
        
   // deliver command to the appropriate module ... 
   LOG4CXX_INFO(logger, "Target module: " + targetModule);    
   
   // command for ARMMOVER module
   if (targetModule.compare("ARMMOV") == 0)
   {
       send2ArmMover(command, pBoneMsg->getDetail());
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
       
       send2JointControl(pBoneMsg->getDetail(), targetJoint);
   }
   // command for JOINT angle
   else if (targetModule.find("POS") != std::string::npos)
   {
       // obtain the target joint from the module symbol
       targetJoint = getTargetJoint(targetModule);
       
       send2DirectJoint(pBoneMsg->getDetail(), targetJoint);
   }
   // command for MANIPULATION area
   else if (targetModule.compare("AMANIP") == 0)
   {
       send2ArmManager(command);
   }
   else 
   {
       LOG4CXX_WARN(logger, "Invalid target module! Message ignored ... " << pBoneMsg->toString());
       return false;
   }
          
   return true;
}

// Commands for ArmMover module
void ManipResponder::send2ArmMover(std::string command, int detail)
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


void ManipResponder::send2JointMover(std::string command, std::string jointName)
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
        pBus->getConnectionsJoint(jointName).getCO_MOVE_ACTION().request(moverAction);            
    else
        LOG4CXX_WARN(logger, "> unknown command!");
}


void ManipResponder::send2JointControl(int detail, std::string jointName)
{
    LOG4CXX_INFO(logger, "> JointControl " << jointName << " - speed = " << detail);    

    // WRITE CO_SOLL_SPEED
    float speed = detail;
    pBus->getConnectionsJoint(jointName).getCO_SOLL_SPEED().request(speed);
}


void ManipResponder::send2DirectJoint(int detail, std::string jointName)
{
    LOG4CXX_INFO(logger, "> Joint " << jointName << " - angle = " << detail);    

    // WRITE CO_SOLL_ANGLE
    float angle = detail;
    pBus->getConnectionsJoint(jointName).getCO_SOLL_ANGLE().request(angle);
}


// Commands for ArmManager area
void ManipResponder::send2ArmManager(std::string command)
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
std::string ManipResponder::getTargetJoint(std::string moduleSymbol)
{
    // extract the joint number from the module symbol
    std::string jointText = moduleSymbol.substr(1, 1);       // J1_MOV, J2_CON, ...
    int jointNum = std::stoi(jointText);
    
    // joint 1 is at position 0 ...
    std::string jointName = listJointNames.at(jointNum-1);
    
    return jointName;
}

void ManipResponder::buildModulesMap()
{
    LOG4CXX_INFO(logger, "Building modules map ...");
    
   // creates a map with the list of supported modules in this area
    std::vector<BoneModul> listModules = oBoneReader.readAreaModules();
    
    for (BoneModul& oBoneModul : listModules)
    {
        mapModules.emplace(oBoneModul.getModule(), oBoneModul.getSymbol());        
    }        
}

void ManipResponder::buildControlsMap()
{
    LOG4CXX_INFO(logger, "Building controls map ...");

    // creates a map with the list of supported modules in this area
    std::vector<BoneSymbol> listControls = oBoneReader.readAreaControls();
    
    for (BoneSymbol& oBoneSymbol : listControls)
    {
        mapControls.emplace(oBoneSymbol.getID(), oBoneSymbol.getSymbol());        
    }        
}

void ManipResponder::showModulesMap()
{
    LOG4CXX_INFO(logger, "ManipResponder modules map:");      
     for (auto& element : mapModules) 
     {
        LOG4CXX_INFO(logger, element.first << ": " << element.second);      
    }    
}

void ManipResponder::showControlsMap()
{
    LOG4CXX_INFO(logger, "ManipResponder controls map:");      
     for (auto& element : mapControls) 
     {
        LOG4CXX_INFO(logger, element.first << ": " << element.second);      
    }    
}

}