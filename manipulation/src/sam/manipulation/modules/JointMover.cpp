/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "JointMover.h"

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
    
// starts movement in the specified joint direction (positive as default) 
void JointMover::move(int direction = 1)
{
    if (direction > 0)
        this->direction = 1;
    else if (direction < 0)
        this->direction = -1;

    setNextState(eSTATE_ACCEL);
}
    
// starts braking until the joint stops        
void JointMover::brake()
{
    setNextState(eSTATE_BRAKE);    
}
        
// keeps the present speed
void JointMover::keep()
{
    setNextState(eSTATE_KEEP);    
}

// suddenly stops the joint
void JointMover::stop()
{
    setNextState(eSTATE_STOP);    
}
                
void JointMover::loop()
{
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
                keep();

            break;
            
        case eSTATE_BRAKE:
            
            doBrake();
            
            if(speed == 0)
                stop();

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