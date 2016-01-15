/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/look/modules/tracker/Tracker.h"
#include "sam/network2/ControlPriority.h"

namespace sam 
{
namespace look
{    
log4cxx::LoggerPtr Tracker::logger(log4cxx::Logger::getLogger("sam.look"));

Tracker::Tracker() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    busConnected = false;
    binhibited = false;
    pBus = 0;
    headPriority = network::ControlPriority::headPriority4Tracker;
    reqPan = 0;   
    reqTilt = 0;
}

void Tracker::init()
{
    binitialized = true;
    LOG4CXX_INFO(logger, "Tracker initialized");             
};

void Tracker::busConnect(Bus& oBus)
{
    pBus = &oBus;
    busConnected = true;
}

void Tracker::first()
{    
    log4cxx::NDC::push("Tracker");   	
    //log4cxx::NDC::push("");   	
    
    // we start in LOST state
    if (binitialized && busConnected && isNetConnected())
    {
        LOG4CXX_INFO(logger, "started");  
        LOG4CXX_WARN(logger, "beginning with START (instead of LOST)");  
        setState(Tracker::eSTATE_START);    // begin with START for test! Real begin with LOST
        setPrevState(utils::Module::state_OFF);
        showStateName();        
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        utils::Module::off();        
    }
}

void Tracker::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Tracker::loop()
{   
    // read bus
    senseBus();

    oClick.read();
    oClick.start();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case Tracker::eSTATE_START:
                        
            // on new target ...
            // keep real head position
            // and assume zero initial target speed
            reqPan = realPan;
            reqTilt = realTilt;
            panSpeed = 0;
            tiltSpeed = 0;
            // TEMP for test. 
            // (Real target speed should be measured)
            panSpeed = 10;  // 10ª/s
            tiltSpeed = 5;  // 5º/s
            counterPan = 0;
            counterTilt = 0;
            // jump -> TRACK
            setState(Tracker::eSTATE_TRACK);            
            break;            

        case Tracker::eSTATE_TRACK:            
                        
            followTarget();
            switchSpeedOnLimit();
            break;            

        case Tracker::eSTATE_LOST:
                        
            // nothing done
            break;            
    }   // end switch    
    
    // write to bus
    writeBus();

    if (isStateChanged())
    {
        showStateName();    
        setPrevState(getState());
    }
}

void Tracker::followTarget()
{
    // update head position with measured target speed
    reqPan += (float)panSpeed * oClick.getMillis() / 1000; 
    reqTilt += (float)tiltSpeed * oClick.getMillis() / 1000;     
    LOG4CXX_INFO(logger, "req: " << reqPan << ", " << reqTilt);
    counterPan++;
    counterTilt++;
}

void Tracker::switchSpeedOnLimit()
{
    // if pan limit reached, switch pan speed
    if (pNetwork->getHeadComs().getSO_HEAD_PAN_LIMIT().getValue() && counterPan > 20)
    {
        panSpeed = -panSpeed;
        counterPan = 0;
        LOG4CXX_WARN(logger, "pan speed switched!");
    }
    
    // if tilt limit reached, switch tilt speed
    if (pNetwork->getHeadComs().getSO_HEAD_TILT_LIMIT().getValue() && counterTilt > 20)
    {
        tiltSpeed = -tiltSpeed;
        counterTilt = 0;
        LOG4CXX_WARN(logger, "tilt speed switched!");
    }
}

void Tracker::senseBus()
{
    realPan = pNetwork->getHeadComs().getSO_HEAD_PAN().getValue();
    realTilt = pNetwork->getHeadComs().getSO_HEAD_TILT().getValue();
}

void Tracker::writeBus()
{
    int pan = (int)reqPan;
    int tilt = (int)reqTilt;
    pNetwork->getHeadComs().getCO_HEAD_PAN().request(pan, headPriority);
    pNetwork->getHeadComs().getCO_HEAD_TILT().request(tilt, headPriority);
}

// Shows the state name
void Tracker::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case Tracker::eSTATE_START:
            stateName = "start";
            break;            

        case Tracker::eSTATE_TRACK:
            stateName = "track";
            break;            

        case Tracker::eSTATE_LOST:
            stateName = "lost";
            break;            
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}