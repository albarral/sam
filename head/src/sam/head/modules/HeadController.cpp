/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/head/modules/HeadController.h"
#include "sam/head/modules/HeadFactory.h"
#include "sam/network2/areas/HeadComs.h"

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
        // force initial frontal gaze
        reqPan = 0;
        reqTilt = 0;
        moveHead();
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
                moveHead();
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

void HeadController::moveHead()
{
    pHead->move(reqPan, reqTilt);
    realPan = pHead->getLimitedPan();
    realTilt = pHead->getLimitedTilt();
    if (pHead->isPanLimited())                    
        LOG4CXX_WARN(logger, "pan exceeds limit");
    if (pHead->isTiltLimited())
        LOG4CXX_WARN(logger, "tilt exceeds max value");
    LOG4CXX_INFO(logger, "real: " << realPan << ", " << realTilt);    
}

// note: it directly senses the network (no bus)
void HeadController::senseBus()
{
    // read CI's ....
    // CO_HEAD_PAN
    bool bpanRequested = pNetwork->getHeadComs().getCO_HEAD_PAN().checkRequested(reqPan);
    // CO_HEAD_TILT
    bool btiltRequested = pNetwork->getHeadComs().getCO_HEAD_TILT().checkRequested(reqTilt);
    bmoveRequested = bpanRequested || btiltRequested;
}

// note: it directly writes to the network (no bus)
void HeadController::writeBus()
{
    network::HeadComs& oHeadComs = pNetwork->getHeadComs();
    // write SO's ... 
    // SO_HEAD_PAN
    oHeadComs.getSO_HEAD_PAN().setValue(realPan);
    // SO_HEAD_TILT
    oHeadComs.getSO_HEAD_TILT().setValue(realTilt);
    // SO_HEAD_PAN_LIMIT
    oHeadComs.getSO_HEAD_PAN_LIMIT().setValue(pHead->isPanLimited());
    // SO_HEAD_TILT_LIMIT
    oHeadComs.getSO_HEAD_TILT_LIMIT().setValue(pHead->isTiltLimited());
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