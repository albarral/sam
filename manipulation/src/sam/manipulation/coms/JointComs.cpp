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

void JointComs::setModuleInterpreter(std::vector<network::NetworkCode>& listAreaComponents)
{
    oModuleInterpreter.clearDictionary();
    
    oModuleInterpreter.addElement("JOINT_MOVER_1", eJOINT_MOVER);
    oModuleInterpreter.addElement("JOINT_MOVER_2", eJOINT_MOVER);
    oModuleInterpreter.addElement("JOINT_MOVER_3", eJOINT_MOVER);
    oModuleInterpreter.addElement("JOINT_MOVER_4", eJOINT_MOVER);
    
    oModuleInterpreter.addElement("JOINT_CONTROL_1", eJOINT_CONTROL);
    oModuleInterpreter.addElement("JOINT_CONTROL_2", eJOINT_CONTROL);
    oModuleInterpreter.addElement("JOINT_CONTROL_3", eJOINT_CONTROL);
    oModuleInterpreter.addElement("JOINT_CONTROL_4", eJOINT_CONTROL);

    oModuleInterpreter.addElement("JOINT_ANGLE_1", eJOINT_POSITION);
    oModuleInterpreter.addElement("JOINT_ANGLE_2", eJOINT_POSITION);
    oModuleInterpreter.addElement("JOINT_ANGLE_3", eJOINT_POSITION);
    oModuleInterpreter.addElement("JOINT_ANGLE_4", eJOINT_POSITION);
    
    oModuleInterpreter.updateTranslator(listAreaComponents);
    LOG4CXX_INFO(logger, "module interpreter set");          
}

void JointComs::setCommandInterpreter(std::vector<network::NetworkCode>& listAreaComponents)
{
    oCommandInterpreter.clearDictionary();

    oCommandInterpreter.addElement("JMOVER_UP", JointMover::eMOV_POSITIVE);
    oCommandInterpreter.addElement("JMOVER_DOWN", JointMover::eMOV_NEGATIVE);
    oCommandInterpreter.addElement("JMOVER_KEEP", JointMover::eMOV_KEEP);
    oCommandInterpreter.addElement("JMOVER_BRAKE", JointMover::eMOV_BRAKE);
    oCommandInterpreter.addElement("JMOVER_STOP", JointMover::eMOV_STOP);

    oCommandInterpreter.updateTranslator(listAreaComponents);
    LOG4CXX_INFO(logger, "control interpreter set");          
}

bool JointComs::processMessage(network::ControlMsg& oControlMsg)
{  
    LOG4CXX_INFO(logger, "process message ... " + oControlMsg.toString());
    int targetModule;
    bool bsentOK = false;
    
    // check that interpreters are enabled
    if (!oModuleInterpreter.isEnabled() || !oCommandInterpreter.isEnabled())
    {
        LOG4CXX_ERROR(logger, "Interpreters disabled. Skip!");          
        return false;
    }

    // check that target module is valid
    if (oModuleInterpreter.translateNetworkCode(oControlMsg.getModuleID()))    
        targetModule = oModuleInterpreter.getAreaCode();
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
            
            bsentOK = send2JointControl((float)oControlMsg.getDetail());
            break;
            
        case eJOINT_POSITION:
            
            bsentOK = send2JointPos((float)oControlMsg.getDetail());
            break;
    }
    
    return bsentOK;
}

bool JointComs::send2JointMover(int networkCommand)
{            
    LOG4CXX_INFO(logger, "send to JointMover - action = " << networkCommand);    
    int moverAction;
    
    // check that target module is valid
    if (oCommandInterpreter.translateNetworkCode(networkCommand))    
        moverAction = oCommandInterpreter.getAreaCode();
    else
    {
        LOG4CXX_ERROR(logger, "Invalid target action " << networkCommand << ". Skip!");          
        return false;        
    }

    pCO_JMOVER_ACTION->request(moverAction);
    return true;
}


bool JointComs::send2JointControl(float jointSpeed)
{
    LOG4CXX_INFO(logger, "send to JointControl - speed = " << jointSpeed);    

    pCO_JCONTROL_SPEED->request(jointSpeed);
    return true;
}


bool JointComs::send2JointPos(float jointAngle)
{
    LOG4CXX_INFO(logger, "send to JointControl - angle = " << jointAngle);    

    pCO_JOINT_ANGLE->request(jointAngle);
    return true;
}


}