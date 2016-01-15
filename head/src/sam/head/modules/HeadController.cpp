/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/head/modules/HeadController.h"
#include "sam/head/modules/HeadFactory.h"

namespace sam 
{
namespace head
{    
log4cxx::LoggerPtr HeadController::logger(log4cxx::Logger::getLogger("sam.head"));

HeadController::HeadController() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    binhibited = false;
    pHead = 0;
}

void HeadController::init(std::string headModel)
{
    // TO DO ... set head type depending on given headModel
    HeadFactory oHeadFactory;        
    pHead = oHeadFactory.createHead(HeadFactory::eHEAD_IPCAMERA2);
    
    if (pHead->connect() == 0)
    {
        binitialized = true;
        LOG4CXX_INFO(logger, "HeadController initialized");             
    }
    else
        LOG4CXX_ERROR(logger, "HeadController NOT initialized!");                 
};

void HeadController::first()
{    
    log4cxx::NDC::push("Head");   	
    //log4cxx::NDC::push("");   	
    
    // we start in LOST state
    if (binitialized && isNetConnected())
    {
        LOG4CXX_INFO(logger, "started");  
        setState(HeadController::eSTATE_ON);    
        setPrevState(utils::Module::state_OFF);
        showStateName();        
    }
    // if not initialized or not connected to network -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        utils::Module::off();        
    }
}

void HeadController::bye()
{
    if (binitialized)
        pHead->disconnect();
    LOG4CXX_INFO(logger, "ended");     
}

void HeadController::loop()
{   
    // read bus
    senseBus();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case HeadController::eSTATE_ON:            
                        
            if (bmoveRequested && pHead->isConnected())
            {
                pHead->move(reqPan, reqTilt);
                realPan = pHead->getLimitedPan();
                realTilt = pHead->getLimitedTilt();
                LOG4CXX_INFO(logger, "real: " << realPan << ", " << realTilt);
            }
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

// note: it directly senses the network (no bus)
void HeadController::senseBus()
{
    // read CI's ....
    // CO_HEAD_PAN
    bool bpanRequested = pNetwork->getCO_HEAD_PAN().checkRequested(reqPan);
    // CO_HEAD_TILT
    bool btiltRequested = pNetwork->getCO_HEAD_TILT().checkRequested(reqTilt);
    bmoveRequested = bpanRequested || btiltRequested;
}

// note: it directly writes to the network (no bus)
void HeadController::writeBus()
{
    // write SO's ... 
    // SO_HEAD_PAN
    pNetwork->getSO_HEAD_PAN().setValue(realPan);
    // SO_HEAD_TILT
    pNetwork->getSO_HEAD_TILT().setValue(realTilt);
}

// Shows the state name
void HeadController::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case HeadController::eSTATE_ON:
            stateName = "on";
            break;            
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}