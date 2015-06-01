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
}

//JointControl::~JointControl()
//{
//}

void JointControl::init(std::string name, Joint& oJoint)
{
    this->name = name;    
    mJoint = &oJoint;
    benabled = true;

    LOG4CXX_INFO(logger, "JointControl " << name << " initialized");      
};

void JointControl::connect(manipulation::ConnectionsJoint& oConnectionsJoint)
{
    pConnectionsJoint = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_INFO(logger, "JointControl " << name << " connected to bus");      
}

void JointControl::first()
{
    setState(eSTATE_GO);
    setNextState(eSTATE_GO);
    log4cxx::NDC::push("on." + name);   	
}
                    
void JointControl::senseBus()
{
    pConnectionsJoint->getCOSpeed().isRequested(reqSpeed);
    speed_ms = reqSpeed/1000.0;
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
    
    writeBus();
}


void JointControl::doSpeed2Angle()
{
    angle += (float)(speed_ms*oClick.getMillis());
    
    // limit angle to joint's range
    if (angle > mJoint->getUpperLimit())
    {
        angle = mJoint->getUpperLimit();
        limitBroken = 1;
    }
    else if (angle < mJoint->getLowerLimit())
    {
        angle = mJoint->getLowerLimit();
        limitBroken = -1;
    }
    else
        limitBroken = 0;
}

void JointControl::writeBus()
{
    int iAngle = angle;
    pConnectionsJoint->getCOAngle().request(iAngle);
    LOG4CXX_INFO(logger, ">> angle = " << angle);
}


}