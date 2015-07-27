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

void ManipResponder::init (manipulation::Config& oConfig)
{
    LOG4CXX_INFO(logger, "ManipResponder: tunning to TAB_COMMANDS " << area << " section");          

    // list of joints
    listJointNames = oConfig.getListJointNames();
    
    // connect the backbone reader & tune it to the commands table
    oBoneReader.init();
    oBoneReader.tune(BoneBase::eTAB_CONTROL, area);
    
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
    std::string targetModule;
    std::string targetJoint;

    // obtain target module for the received message
    try
    {
        targetModule = mapModules.at(pBoneMsg->getModuleID());
    }
    catch (std::out_of_range)
    {
        LOG4CXX_ERROR(logger, "Invalid message: module ID not found in map! - " << pBoneMsg->toString());
        return false;
    }
        
   // deliver command to the appropriate module  
   std::string word_ArmMover =  "arm_mover";
   std::string word_JointMover =  "jointmover";
   std::string word_JointControl = "jointcontrol";
   
   // TO ARMMOVER module
   if (targetModule.find(word_ArmMover) != std::string::npos)
   {
       send2ArmMover(pBoneMsg->getInfo(), pBoneMsg->getDetail());
   }
   // TO JOINTMOVER module
   else if (targetModule.find(word_JointMover) != std::string::npos)
   {
       targetJoint = extractTargetJoint(targetModule);
       
       if (targetJoint.size() > 0)
        send2JointMover(pBoneMsg->getInfo(), pBoneMsg->getDetail(), targetJoint);
   }
   // TO JOINTCONTROL module
   else if (targetModule.find(word_JointControl) != std::string::npos)
   {
       targetJoint = extractTargetJoint(targetModule);
       
       if (targetJoint.size() > 0)
           send2JointControl(pBoneMsg->getInfo(), pBoneMsg->getDetail(), targetJoint);
   }
   else 
   {
       LOG4CXX_WARN(logger, "Ignored message: target not used! - " << pBoneMsg->toString());
       return false;
   }
          
   return true;
}

// extracts the joint name from the target module string
std::string ManipResponder::extractTargetJoint(std::string targetModule)
{
    for (std::string& jointName : listJointNames)
    {
        if (targetModule.find(jointName) != std::string::npos)
            return jointName;
    }
    return "";
}

// Commands for ArmMover module
void ManipResponder::send2ArmMover(std::string info, int detail)
{    
    std::string word_start = "start";
    std::string word_stop = "stop";

    // CO start
    if (info.find(word_start) != std::string::npos)
        pBus->getCOArmMoverStart().request(); 
    // CO stop
    else if (info.find(word_stop) != std::string::npos)
        pBus->getCOArmMoverStop().request();            
    else
        LOG4CXX_WARN(logger, "> wrong ArmMover command requested: " << info);
}

void ManipResponder::send2JointMover(std::string info, int detail, std::string jointName)
{    
    int reqCommand = -1;
    std::string word_movePos = "move+";
    std::string word_moveNeg = "move-";
    std::string word_brake = "brake";
    std::string word_stop = "stop";

    if (info.find(word_movePos) != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_POSITIVE;
    else if (info.find(word_moveNeg) != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_NEGATIVE;
    else if (info.find(word_brake) != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_BRAKE;
    else if (info.find(word_stop) != std::string::npos)
        reqCommand = manipulation::Commands::eJOINT_STOP;
    
    if (reqCommand >=0 )        
        pBus->getConnectionsJoint(jointName).getCOAction().request(reqCommand);            
    else
        LOG4CXX_WARN(logger, "> wrong JointMover command requested: " << info);
}

void ManipResponder::send2JointControl(std::string info, int detail, std::string jointName)
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