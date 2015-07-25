/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range
#include "log4cxx/ndc.h"

#include "ManipResponder.h"
#include "sam/backbone/data/BoneModul.h"
#include "sam/backbone/data/BoneMsg.h"

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

void ManipResponder::init ()
{
    LOG4CXX_INFO(logger, "ManipResponder: tunning to TAB_COMMANDS " << area << " section");          

    // connect the backbone reader & tune it to the commands table
    oBoneReader.init();
    oBoneReader.tune(BoneBase::eTAB_COMMANDS, area);
    
    // if connected, create the modules map (for interpreting the received messages)
    if (oBoneReader.isReady())
    {
        buildModulesMap();
        benabled = true;    
        LOG4CXX_INFO(logger, "ManipResponder: initialized ok");          
        showModulesMap();
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
    bool bvalid = false;
    
//    LOG4CXX_INFO(logger, "> ?");    
//    oResponder.listen();
//
//    int commandID = oResponder.getCommandID();
//    
//    // list of expected words
//    if (commandID != Responder::UNRECOGNIZED_WORD)
//    {
//        bvalid = true;
//        LOG4CXX_INFO(logger, oResponder.getRawCommand());      
//        
//        // finish all?
//        if (commandID == manipulation::Commands::eFINISH_ALL)
//            pBus->getConnections().getCOFinish().request();            
//        else if (manipulation::Commands::isArmMoverCommand(oResponder.getRawCommand()))        
//            sendArmMoverCommand(commandID);
//        else
//            sendJointCommand(commandID);
//    }
//    // not in the list (numerics accepted)
//    else
//    {
//        int numCommand = 0;        
//        LOG4CXX_INFO(logger, oResponder.getRawCommand());      
//
//        if (oResponder.isNumericCommand(numCommand))
//        {
//            bvalid = true;
//            sendJointAngle(numCommand);
//        }
//    }
      
    if (!bvalid)
        LOG4CXX_ERROR(logger, "Invalid command!");
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
            oBoneReader.markMessageOk(pBoneMsg->getModuleID());
        else
            oBoneReader.markMessageFailed(pBoneMsg->getModuleID());
    }    
}

bool ManipResponder::processMessage(BoneMsg* pBoneMsg)
{
    std::string module;
    std::string target1, target2, target3;
    std::string targetJoint;

    // obtain target module of message
    try
    {
        module = mapModules.at(pBoneMsg->getModuleID());
    }
    catch (std::out_of_range)
    {
        LOG4CXX_ERROR(logger, "Invalid message: module ID not found in map! - " << pBoneMsg->toString());
        return false;
    }
        
   // deliver command to appropriate module  
   target1 = "arm_mover";
   target2 = "mover";
   target3 = "control";
   if (module.find(target1) != std::string::npos)
       sendArmMover(pBoneMsg->getInfo(), pBoneMsg->getDetail());
   else if (module.find(target2) != std::string::npos)
   {
       targetJoint = "v_shoulder";
       sendJointMover(pBoneMsg->getInfo(), pBoneMsg->getDetail(), targetJoint);
   }
   else if (module.find(target3) != std::string::npos)
   {
       targetJoint = "v_shoulder";
       sendJointControl(pBoneMsg->getInfo(), pBoneMsg->getDetail(), targetJoint);
   }
   else 
   {
       LOG4CXX_WARN(logger, "Ignored message: target not used! - " << pBoneMsg->toString());
       return false;
   }
          
   return true;
}

void ManipResponder::sendArmMover(std::string info, int detail)
{    
    std::string command1 = "start";
    std::string command2 = "stop";

    if (info.find(command1) != std::string::npos)
        pBus->getCOArmMoverStart().request(); 
    else if (info.find(command2) != std::string::npos)
        pBus->getCOArmMoverStop().request();            
    else
        LOG4CXX_WARN(logger, "> unknown arm mover command: " << info);
}

void ManipResponder::sendJointMover(std::string info, int detail, std::string jointName)
{    
    LOG4CXX_WARN(logger, " TO DO ...")
//    switch (reqCommand)
//    {        
//        case manipulation::Commands::eJOINT_POSITIVE:
//        case manipulation::Commands::eJOINT_NEGATIVE:
//        case manipulation::Commands::eJOINT_BRAKE:
//        case manipulation::Commands::eJOINT_KEEP:
//        case manipulation::Commands::eJOINT_STOP:            
//            pBus->getConnectionsJoint(activeJointName).getCOAction().request(reqCommand);            
//            break;
// 
//        case manipulation::Commands::eJOINT_USE1:
//        case manipulation::Commands::eJOINT_USE2:
//        case manipulation::Commands::eJOINT_USE3:
//        case manipulation::Commands::eJOINT_USE4:
//        {
//            // sets the name of the active joint
//            int index = reqCommand - manipulation::Commands::eJOINT_USE1;
//            activeJointName = listJointNames.at(index);
//            LOG4CXX_INFO(logger, "active joint = " << activeJointName);
//            break;
//        }
//
//        default:
//            LOG4CXX_INFO(logger, "> wrong joint command requested");
//            break;
//    }    
}

void ManipResponder::sendJointControl(std::string info, int detail, std::string jointName)
{
    LOG4CXX_WARN(logger, " TO DO ...")
//    float angle = angleCommand;
//        
//    pBus->getConnectionsJoint(activeJointName).getCOAngle().request(angle);
//    LOG4CXX_INFO(logger, "angle=" << angleCommand);
}


void ManipResponder::buildModulesMap()
{
    // creates a map with the list of supported modules in this area
    std::vector<BoneModul>& listModules = oBoneReader.getListModules();
    
    for (BoneModul& oBoneModul : listModules)
    {
        mapModules.emplace(oBoneModul.getModuleID(), oBoneModul.getModule());        
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

}