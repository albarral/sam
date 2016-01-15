/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/look/modules/tracker/Tracker.h"

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
        setState(Tracker::eSTATE_ON);    
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
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case Tracker::eSTATE_ON:            
                        
            reqPan = 30;
            reqTilt = 30;
            LOG4CXX_INFO(logger, "req: " << reqPan << ", " << reqTilt);
            break;            
    }   // end switch    
    
    if (isStateChanged())
    {
        showStateName();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void Tracker::senseBus()
{
    // read CI's ....
    // CO_HEAD_PAN
    // CO_HEAD_TILT
//    bool bpanRequested = pBus->getCOBus().getCO_HEAD_PAN().checkRequested(reqPan);
//    bool btiltRequested = pBus->getCOBus().getCO_HEAD_TILT().checkRequested(reqTilt);
//    bmoveRequested = bpanRequested || btiltRequested;
}

void Tracker::writeBus()
{
    pNetwork->getCO_HEAD_PAN().request(reqPan, 1);
    pNetwork->getCO_HEAD_TILT().request(reqTilt, 1);
}

// Shows the state name
void Tracker::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case Tracker::eSTATE_ON:
            stateName = "on";
            break;            
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}