/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range
#include "log4cxx/ndc.h"

#include "ManipResponder.h"
#include "sam/backbone/data/BoneModul.h"
#include "sam/backbone/data/BoneMsg.h"
#include "Commands.h"

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
    LOG4CXX_INFO(logger, "ManipResponder: tunning to TAB_COMMANDS " << area << " section");          
    
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
    LOG4CXX_INFO(logger, "> check messages");    
    check4NewMessages();      
}


void ManipResponder::check4NewMessages()
{
    BoneMsg* pBoneMsg = 0;

    // read messages from DB
    oBoneReader.readMessages();
    
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
    std::string targetCommand;   // a control symbol

    // obtain target module for the received message
    try
    {
        targetModule = mapModules.at(pBoneMsg->getModule());
        targetCommand = mapControls.at(pBoneMsg->getInfo());
    }
    catch (std::out_of_range)
    {
        LOG4CXX_ERROR(logger, "Invalid message: module or command not supported! - " << pBoneMsg->toString());
        return false;
    }
        
   // deliver command to the appropriate module ... 
   
   // ARMMOVER module
   if (targetModule.compare("ARMMOV") == 0)
   {
       send2ArmMover(targetCommand, pBoneMsg->getDetail());
   }
   // JOINTMOVER modules
   else if (targetModule.find("MOV") != std::string::npos)
   {
       targetJoint = getTargetJoint(targetModule);
       
       send2JointMover(targetCommand, pBoneMsg->getDetail(), targetJoint);
   }
   // JOINTCONTROL modules
   else if (targetModule.find("CON") != std::string::npos)
   {
       targetJoint = getTargetJoint(targetModule);
       
       send2JointControl(targetCommand, pBoneMsg->getDetail(), targetJoint);
   }
   else 
   {
       LOG4CXX_WARN(logger, "Ignored message: target not used! - " << pBoneMsg->toString());
       return false;
   }
          
   return true;
}


// Commands for ArmMover module
void ManipResponder::send2ArmMover(std::string commandSymbol, int detail)
{    
    // CO start
    if (commandSymbol.find("START") != std::string::npos)
        pBus->getCOArmMoverStart().request(); 
    // CO stop
    else if (commandSymbol.find("STOP") != std::string::npos)
        pBus->getCOArmMoverStop().request();            
    else
        LOG4CXX_WARN(logger, "> wrong ArmMover command requested: " << commandSymbol);
}

void ManipResponder::send2JointMover(std::string command, int detail, std::string jointName)
{    
    int reqCommand = -1;

    if (command.find("MOVPOS") != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_POSITIVE;
    else if (command.find("MOVNEG") != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_NEGATIVE;
    else if (command.find("BRAKE") != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_BRAKE;
    else if (command.find("STOP") != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_STOP;
    
    if (reqCommand >=0 )        
        pBus->getConnectionsJoint(jointName).getCOAction().request(reqCommand);            
    else
        LOG4CXX_WARN(logger, "> wrong JointMover command requested: " << command);
}

void ManipResponder::send2JointControl(std::string info, int detail, std::string jointName)
{
    LOG4CXX_WARN(logger, " TO DO ...")
//    float angle = angleCommand;
//        
//    pBus->getConnectionsJoint(activeJointName).getCOAngle().request(angle);
//    LOG4CXX_INFO(logger, "angle=" << angleCommand);
}


// extracts the joint name from the target module symbol
std::string ManipResponder::getTargetJoint(std::string moduleSymbol)
{
    // extract the joint number from the module symbol
    // first joint number is 1
    std::string jointText = moduleSymbol.substr(1, 1);       // J1_MOV, J2_CON, ...
    int jointNum = std::stoi(jointText);
    
    // joint 1 is at position 0 ...
    std::string jointName = listJointNames.at(jointNum-1);
    
    return jointName;
}

void ManipResponder::buildModulesMap()
{
    // creates a map with the list of supported modules in this area
    std::vector<BoneModul> listModules = oBoneReader.readAreaModules();
    
    for (BoneModul& oBoneModul : listModules)
    {
        mapModules.emplace(oBoneModul.getModule(), oBoneModul.getSymbol());        
    }        
}

void ManipResponder::buildControlsMap()
{
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