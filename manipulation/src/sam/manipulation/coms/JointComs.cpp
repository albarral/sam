/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range
#include "log4cxx/ndc.h"

#include "JointComs.h"
#include "sam/manipulation/modules/JointMover.h"


using namespace log4cxx;

namespace sam
{
LoggerPtr JointComs::logger(Logger::getLogger("sam.manipulation"));

// Constructor 
JointComs::JointComs ()
{           
    benabled = false;
 }

// Destructor
JointComs::~JointComs ()
{
}

void JointComs::init(std::string jointName, manipulation::Bus& oBus)
{      
    this->jointName = jointName;
    
    log4cxx::NDC::push("JointComs-" + jointName);  
    
    manipulation::ConnectionsJoint& oConnectionsJoint = oBus.getConnectionsJoint(jointName);
    pCO_JMOVER_ACTION = &(oConnectionsJoint.getCO_JMOVER_ACTION());     // JointMover commands
    pCO_JCONTROL_SPEED = &(oConnectionsJoint.getCO_JCONTROL_SPEED());    // JointControl commands
    pCO_JOINT_ANGLE = &(oConnectionsJoint.getCO_JOINT_ANGLE());           // Direct joint commands
    
    benabled = true;
    LOG4CXX_INFO(logger, "Initialized");          
}

void JointComs::setModuleInterpreter(std::vector<network::AreaComponent>& listAreaComponents)
{
    oModuleInterpreter.clearKnowledge();
    
    oModuleInterpreter.addKnowledgeItem("JOINT_MOVER_1", eJOINT_MOVER);
    oModuleInterpreter.addKnowledgeItem("JOINT_MOVER_2", eJOINT_MOVER);
    oModuleInterpreter.addKnowledgeItem("JOINT_MOVER_3", eJOINT_MOVER);
    oModuleInterpreter.addKnowledgeItem("JOINT_MOVER_4", eJOINT_MOVER);
    
    oModuleInterpreter.addKnowledgeItem("JOINT_CONTROL_1", eJOINT_CONTROL);
    oModuleInterpreter.addKnowledgeItem("JOINT_CONTROL_2", eJOINT_CONTROL);
    oModuleInterpreter.addKnowledgeItem("JOINT_CONTROL_3", eJOINT_CONTROL);
    oModuleInterpreter.addKnowledgeItem("JOINT_CONTROL_4", eJOINT_CONTROL);

    oModuleInterpreter.addKnowledgeItem("JOINT_ANGLE_1", eJOINT_DIRECT);
    oModuleInterpreter.addKnowledgeItem("JOINT_ANGLE_2", eJOINT_DIRECT);
    oModuleInterpreter.addKnowledgeItem("JOINT_ANGLE_3", eJOINT_DIRECT);
    oModuleInterpreter.addKnowledgeItem("JOINT_ANGLE_4", eJOINT_DIRECT);
    
    oModuleInterpreter.buildTranslator(listAreaComponents);
    LOG4CXX_INFO(logger, "module interpreter set");          
}

void JointComs::setControlInterpreter(std::vector<network::AreaComponent>& listAreaComponents)
{
    oControlInterpreter.clearKnowledge();

    oControlInterpreter.addKnowledgeItem("JMOVER_UP", JointMover::eMOV_POSITIVE);
    oControlInterpreter.addKnowledgeItem("JMOVER_DOWN", JointMover::eMOV_NEGATIVE);
    oControlInterpreter.addKnowledgeItem("JMOVER_KEEP", JointMover::eMOV_KEEP);
    oControlInterpreter.addKnowledgeItem("JMOVER_BRAKE", JointMover::eMOV_BRAKE);
    oControlInterpreter.addKnowledgeItem("JMOVER_STOP", JointMover::eMOV_STOP);

    oControlInterpreter.buildTranslator(listAreaComponents);
    LOG4CXX_INFO(logger, "control interpreter set");          
}

bool JointComs::processMessage(network::ControlMsg& oControlMsg)
{  
    LOG4CXX_INFO(logger, "process message ... " + oControlMsg.toString());
    int targetModule;
    bool bsentOK = false;
    
    // check that interpreters are enabled
    if (!oModuleInterpreter.isEnabled() || !oControlInterpreter.isEnabled())
    {
        LOG4CXX_ERROR(logger, "Interpreters disabled. Skip!");          
        return false;
    }

    // check that target module is valid
    if (oModuleInterpreter.checkNetInfo(oControlMsg.getModuleID()))    
        targetModule = oModuleInterpreter.getAreaInfo();
    else
    {
        LOG4CXX_ERROR(logger, "Invalid target module " << oControlMsg.getModuleID() << ". Skip!");          
        return false;
    }
    
    // if valid module, send command to bus
    switch (targetModule)
    {
        case eJOINT_MOVER:            
            
            bsentOK = send2JointMover(oControlMsg.getActionID());
            break;
            
        case eJOINT_CONTROL:
            
            bsentOK = send2JointControl(oControlMsg.getDetail());
            break;
            
        case eJOINT_DIRECT:
            
            bsentOK = send2DirectJoint(oControlMsg.getDetail());
            break;
    }
    
    return bsentOK;
}

bool JointComs::send2JointMover(int netAction)
{            
    LOG4CXX_INFO(logger, "send to JointMover - action = " << netAction);    
    int moverAction;
    
    // check that target module is valid
    if (oControlInterpreter.checkNetInfo(netAction))    
        moverAction = oControlInterpreter.getAreaInfo();
    else
    {
        LOG4CXX_ERROR(logger, "Invalid target action " << netAction << ". Skip!");          
        return false;        
    }

    pCO_JMOVER_ACTION->request(moverAction);
    return true;
}


bool JointComs::send2JointControl(int detail)
{
    LOG4CXX_INFO(logger, "send to JointControl - speed = " << detail);    

    float speed = detail;
    pCO_JCONTROL_SPEED->request(speed);
    return true;
}


bool JointComs::send2DirectJoint(int detail)
{
    LOG4CXX_INFO(logger, "send to JointControl - angle = " << detail);    

    float angle = detail;
    pCO_JOINT_ANGLE->request(angle);
    return true;
}


}