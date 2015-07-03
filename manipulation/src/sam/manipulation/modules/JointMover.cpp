/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "JointMover.h"
#include "sam/manipulation/modules/Commands.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr JointMover::logger(Logger::getLogger("sam.manipulation"));

JointMover::JointMover()
{
    benabled = false;
    direction = 0;
    speed = 0;
    
    bconnected = false;
    pConnectionsJoint = 0;
}

//JointMover::~JointMover()
//{
//}

void JointMover::init(std::string jointName, manipulation::ParamsJointMover& oParamsJointMover)
{
    // all params must be positive
    if (oParamsJointMover.getAccel() <= 0 || 
       oParamsJointMover.getMaxSpeed() <= 0 ||
       oParamsJointMover.getDeaccel() <= 0)
        return;

    modName = jointName;
    accel = oParamsJointMover.getAccel();
    maxSpeed = oParamsJointMover.getMaxSpeed();
    deaccel = oParamsJointMover.getDeaccel();
    accel_ms = (float)this->accel/1000;
    deaccel_ms = (float)this->deaccel/1000;
    benabled = true;

    LOG4CXX_INFO(logger, "JointMover: " << modName << " initialized");      
    LOG4CXX_INFO(logger, "a=" << accel << ", maxSpeed=" << maxSpeed << ", deaccel=" << deaccel);      
};

void JointMover::connect(manipulation::ConnectionsJoint& oConnectionsJoint)
{
    pConnectionsJoint = &oConnectionsJoint;
    bconnected = true;

    LOG4CXX_INFO(logger, "JointMover: " << modName << " connected to bus");      
}

void JointMover::first()
{
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);
    
    log4cxx::NDC::push(modName + "-stop");   	
}
                    
void JointMover::loop()
{
    senseBus();
    
    if (updateState())
        showState();
    
    oClick.read();
    oClick.start();
      
    switch (getState())
    {
        case eSTATE_ACCEL:
            {

                bool bmaxReached = doAccel();

                // if max speed reached -> go to KEEP state
                if (bmaxReached)
                    setNextState(eSTATE_KEEP);
            }
            break;
            
        case eSTATE_BRAKE:
            
            doBrake();
            
            if(speed == 0)
                setNextState(eSTATE_STOP);    

            break;
                    
        case eSTATE_KEEP:
            
            // nothing done
            break;
            
        case eSTATE_STOP:
            
            // abruptly reduces speed to 0
            if(speed != 0)
                speed = 0;
            break;
    }   // end switch    
    
    writeBus();
}

void JointMover::senseBus()
{
    int reqCommand;
    if (pConnectionsJoint->getCOAction().checkRequested(reqCommand))
    {
        processActionRequest(reqCommand);
    }    
}

void JointMover::writeBus()
{
    pConnectionsJoint->getCOSpeed().request(speed);
    
    if(speed != lastOutput)
    {
        LOG4CXX_INFO(logger, "speed = " << (int)speed);
        lastOutput = speed;    
    }
}

void JointMover::processActionRequest(int reqCommand)
{
    switch (reqCommand)
    {
        // start movement to the right (or up if vertical) 
        case manipulation::Commands::eJOINT_RIGHT:
            this->direction = 1;
            setNextState(eSTATE_ACCEL);
            break;
            
        // start movement to the left (or down if vertical) 
        case manipulation::Commands::eJOINT_LEFT:
            this->direction = -1;
            setNextState(eSTATE_ACCEL);
            break;

        // start braking until the joint stops        
        case manipulation::Commands::eJOINT_BRAKE:
            setNextState(eSTATE_BRAKE);    
            break;
            
        // keeps the present speed
        case manipulation::Commands::eJOINT_KEEP:
            setNextState(eSTATE_KEEP);
            break;
            
        // suddenly stops the joint
        case manipulation::Commands::eJOINT_STOP:
            setNextState(eSTATE_STOP);    
            break;

        default:
            LOG4CXX_INFO(logger, "> unkown request");
            break;
    }    
}


// Increase speed in the proper direction. Returns true if max speed reached.
bool JointMover::doAccel()
{
    speed += (float)(direction*accel_ms*oClick.getMillis());

    // limit speed to max value 
    if (abs(speed)>=maxSpeed)
    {
        speed = (speed > 0 ? maxSpeed : -maxSpeed);
        return true;
    }
    else 
        return false;
}

// decrease speed in the proper direction
void JointMover::doBrake()
{
    speed -= (float)(direction*deaccel_ms*oClick.getMillis());

    // set speed to 0 when overdecreased 
    if ((direction > 0 && speed < 0) ||
        (direction < 0 && speed > 0))
    {
        speed = 0;
    }
}

void JointMover::showState()
{
    switch (getState())
    {
        case eSTATE_ACCEL:
            LOG4CXX_INFO(logger, ">> accel");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-accel");   	
            break;
            
        case eSTATE_BRAKE:
            LOG4CXX_INFO(logger, ">> brake");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-brake");   	
            break;
                    
        case eSTATE_KEEP:
            LOG4CXX_INFO(logger, ">> keep");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-keep");   	
            break;
            
        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            log4cxx::NDC::pop();	          
            log4cxx::NDC::push(modName + "-stop");   	
            break;
    }   // end switch    
}

}