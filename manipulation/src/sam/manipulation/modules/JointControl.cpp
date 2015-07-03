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
    angle = 0;
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
    
    if (angle != lastAngle)
    {
        writeBus();
        lastAngle = angle;
    }
}

void JointControl::senseBus()
{
    // read the system's last requested angle
    pConnectionsJoint->getCOAngle().getValue(angle);
    // check for new speed requests
    if (pConnectionsJoint->getCOSpeed().checkRequested(reqSpeed))
        speed_ms = reqSpeed/1000.0;
}

void JointControl::writeBus()
{
    pConnectionsJoint->getCOAngle().request(angle);
    LOG4CXX_DEBUG(logger, "angle=" << (int)angle);
    
    // TEMPORAL: real speed should be obtained from changes in real joint positions
    // for now we put the requested speed
    pConnectionsJoint->getSORealSpeed().setValue(reqSpeed);
}

void JointControl::doSpeed2Angle()
{
    if (speed_ms == 0)
        return;
    
    angle += (float)(speed_ms*oClick.getMillis());      
    
    // limit angle to joint's range
    if (angle > mJoint->getUpperLimit())
    {
        LOG4CXX_WARN(logger, "upper limit!");
        angle = mJoint->getUpperLimit();
        limitBroken = 1;
    }
    else if (angle < mJoint->getLowerLimit())
    {
        LOG4CXX_WARN(logger, "lower limit!");
        angle = mJoint->getLowerLimit();
        limitBroken = -1;
    }
    else
        limitBroken = 0;
}


}