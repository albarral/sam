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
    mBus = 0;
}

//JointMover::~JointMover()
//{
//}

void JointMover::init(std::string name, manipulation::ParamsJointMover& oParamsJointMover)
{
    // all params must be positive
    if (oParamsJointMover.getAccel() <= 0 || 
       oParamsJointMover.getMaxSpeed() <= 0 ||
       oParamsJointMover.getDeaccel() <= 0)
        return;

    this->name = name;    
    accel = oParamsJointMover.getAccel();
    maxSpeed = oParamsJointMover.getMaxSpeed();
    deaccel = oParamsJointMover.getDeaccel();
    accel_ms = (float)this->accel/1000;
    deaccel_ms = (float)this->deaccel/1000;
    benabled = true;

    LOG4CXX_INFO(logger, "JointMover " << name << " initialized: a = " << accel << ", maxSpeed = " << maxSpeed << ", deaccel = " << deaccel);      
};

void JointMover::connect(manipulation::Bus& oBus)
{
    mBus = &oBus;
    bconnected = true;

    LOG4CXX_INFO(logger, "JointMover " << name << " connected to bus");      
}

void JointMover::first()
{
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);
}
                    
void JointMover::senseBus()
{
    int reqCommand;
    if (mBus->getConnections().getShoulderConnectionsH().getCOAction().isRequested(reqCommand))
    {
        processActionRequest(reqCommand);
    }    
}

void JointMover::processActionRequest(int reqCommand)
{
    switch (reqCommand)
    {
        // start movement to the right (or up if vertical) 
        case manipulation::Commands::eMOVER_MOVE_R:
            this->direction = 1;
            setNextState(eSTATE_ACCEL);
            break;
            
        // start movement to the left (or down if vertical) 
        case manipulation::Commands::eMOVER_MOVE_L:
            this->direction = -1;
            setNextState(eSTATE_ACCEL);
            break;

        // start braking until the joint stops        
        case manipulation::Commands::eMOVER_BRAKE:
            setNextState(eSTATE_BRAKE);    
            break;
            
        // keeps the present speed
        case manipulation::Commands::eMOVER_KEEP:
            setNextState(eSTATE_KEEP);
            break;
            
        // suddenly stops the joint
        case manipulation::Commands::eMOVER_STOP:
            setNextState(eSTATE_STOP);    
            break;

        default:
            LOG4CXX_INFO(logger, "> unkown request");
            break;
    }    
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
            
            doAccel();
            
            // if max speed reached -> go to KEEP state
            if (abs(speed) == maxSpeed)
                setNextState(eSTATE_KEEP);

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


// increase speed in the proper direction
void JointMover::doAccel()
{
    speed += (float)(direction*oClick.getMillis()*accel_ms);

    // limit speed to max value 
    if (abs(speed)>maxSpeed)
    {
        speed = (speed > 0 ? maxSpeed : -maxSpeed);
    }
}

// decrease speed in the proper direction
void JointMover::doBrake()
{
    speed -= (float)(direction*oClick.getMillis()*deaccel_ms);

    // set speed to 0 when overdecreased 
    if ((direction > 0 && speed < 0) ||
        (direction < 0 && speed > 0))
    {
        speed = 0;
    }
}

void JointMover::writeBus()
{
    mBus->getConnections().getShoulderConnectionsH().getCOSpeed().request(speed);
    LOG4CXX_INFO(logger, ">> speed = " << speed);
}

void JointMover::showState()
{
    log4cxx::NDC::pop();	

    switch (getState())
    {
        case eSTATE_ACCEL:
            LOG4CXX_INFO(logger, ">> accel");
            log4cxx::NDC::push("accel");   	
            break;
            
        case eSTATE_BRAKE:
            LOG4CXX_INFO(logger, ">> brake");
            log4cxx::NDC::push("brake");   	
            break;
                    
        case eSTATE_KEEP:
            LOG4CXX_INFO(logger, ">> keep");
            log4cxx::NDC::push("keep");   	
            break;
            
        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            log4cxx::NDC::push("stop");   	
            break;
    }   // end switch    
}

}