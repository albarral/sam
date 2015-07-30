/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "JointControl.h"
#include "sam/manipulation/modules/Commands.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr JointControl::logger(Logger::getLogger("sam.manipulation"));

JointControl::JointControl()
{
    benabled = false;
    bconnected = false;
    pConnectionsJoint = 0;
    sollAngle = 0;
    limitBroken = 0;
}

//JointControl::~JointControl()
//{
//}

void JointControl::init(std::string jointName, Joint& oJoint)
{
    modName = jointName + "-pos";
    mJoint = &oJoint;
    benabled = true;

    LOG4CXX_INFO(logger, "JointControl: " << modName << " initialized");      
    LOG4CXX_INFO(logger, "joint range= " << mJoint->getLowerLimit() << ", " << mJoint->getUpperLimit());
};

void JointControl::connect(manipulation::ConnectionsJoint& oConnectionsJoint)
{
    pConnectionsJoint = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_INFO(logger, "JointControl: " << modName << " connected to bus");      
}

void JointControl::first()
{
    setState(eSTATE_GO);
    setNextState(eSTATE_GO);
    
    // angle = read from ist angle
    
    log4cxx::NDC::push(modName);   	
}
                    
void JointControl::loop()
{
    senseBus();
    
    updateState();
    
    oClick.read();
    oClick.start();
      
    switch (getState())
    {
        case eSTATE_GO:            

            doSpeed2Angle();
            break;
    }   // end switch    
    
    if (sollAngle != prevSollAngle)
    {
        writeBus();
        prevSollAngle = sollAngle;
    }
}

void JointControl::senseBus()
{
    // read CO_SOLL_ANGLE 
    // to get the last systembroad SOLL angle
    pConnectionsJoint->getCO_SOLL_ANGLE().getValue(sollAngle);
    
    // read CO_SOLL_SPEED 
    // to check for new SOLL speed requests
    if (pConnectionsJoint->getCO_SOLL_SPEED().checkRequested(sollSpeed))
        sollSpeed_ms = sollSpeed/1000.0;
}

void JointControl::writeBus()
{
    // write CO_SOLL_ANGLE
    // to request a new SOLL angle
    pConnectionsJoint->getCO_SOLL_ANGLE().request(sollAngle);
    LOG4CXX_DEBUG(logger, "angle=" << (int)sollAngle);
    
    // write SO_REALSPEED
    // to inform about the real IST speed
    // TEMPORAL !!! 
    // We put the SOLL speed here instead of the IST speed. 
    // That's because we are not reading the IST angles yet, needed for its computation.
    pConnectionsJoint->getSO_REAL_SPEED().setValue(sollSpeed);
}

void JointControl::doSpeed2Angle()
{
    if (sollSpeed_ms == 0)
        return;
    
    sollAngle += (float)(sollSpeed_ms*oClick.getMillis());      
    
    // limit angle to joint's range
    if (sollAngle > mJoint->getUpperLimit())
    {
        LOG4CXX_WARN(logger, "upper limit!");
        sollAngle = mJoint->getUpperLimit();
        limitBroken = 1;
    }
    else if (sollAngle < mJoint->getLowerLimit())
    {
        LOG4CXX_WARN(logger, "lower limit!");
        sollAngle = mJoint->getLowerLimit();
        limitBroken = -1;
    }
    else
        limitBroken = 0;
}


}