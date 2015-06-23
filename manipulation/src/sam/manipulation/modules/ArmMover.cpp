/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "ArmMover.h"
#include "sam/manipulation/modules/Commands.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr ArmMover::logger(Logger::getLogger("sam.manipulation"));

ArmMover::ArmMover()
{
    benabled = false;
    
    bconnected = false;
    pConnections = 0;
}

//ArmMover::~ArmMover()
//{
//}

void ArmMover::init(int timeChange)
{
    // all params must be positive
    if (timeChange <= 0)
        return;

    modName = "ArmMover";
    this->timeChange = timeChange;
    benabled = true;

    LOG4CXX_INFO(logger, modName << " initialized");      
    LOG4CXX_INFO(logger, "tchange=" << timeChange);      
};

void ArmMover::connect(manipulation::Connections& oConnections)
{
    pConnections = &oConnections;
    bconnected = true;

    LOG4CXX_INFO(logger, modName << " connected to bus");      
}

void ArmMover::first()
{
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);
    oClick.start();
    
    log4cxx::NDC::push(modName + "-stop");   	
}
                    
void ArmMover::loop()
{
    senseSpeed();

    updateState();
//    if (updateState())
//        showState();
    
    oClick.read();
      
    switch (getState())
    {
        case eSTATE_RIGHT:
            
            if (oClick.getMillis() > timeChange)
            {
                writeBus(manipulation::Commands::eMOVER_LEFT);
                prevState = eSTATE_RIGHT;
                setNextState(eSTATE_CHANGE);
            }
            break;
            
        case eSTATE_CHANGE:
            
            if (prevState == eSTATE_RIGHT && realSpeed < 0)
            {
                setNextState(eSTATE_LEFT);
                oClick.start();
            }
            else if (prevState == eSTATE_LEFT && realSpeed > 0)
            {
                setNextState(eSTATE_RIGHT);
                oClick.start();
            }

            break;
                    
        case eSTATE_LEFT:
            
            if (oClick.getMillis() > timeChange)
            {
                writeBus(manipulation::Commands::eMOVER_RIGHT);
                prevState = eSTATE_LEFT;
                setNextState(eSTATE_CHANGE);
            }
            break;
            
        case eSTATE_STOP:

            if (realSpeed != 0)
                writeBus(manipulation::Commands::eMOVER_STOP);
            break;
    }   // end switch        
}

void ArmMover::senseSpeed()
{
    realSpeed = pConnections->getConnectionsJoint("shoulderH").getSORealSpeed().getValue();
}

void ArmMover::writeBus(int command)
{
    pConnections->getConnectionsJoint("shoulderH").getCOAction().request(command);
    
    LOG4CXX_DEBUG(logger, "command = " << command);
}

void ArmMover::start()
{
    setNextState(eSTATE_RIGHT);
    oClick.start();
    
    log4cxx::NDC::push(modName + "-start");   	
}

void ArmMover::stop()
{
    setNextState(eSTATE_STOP);
    
    log4cxx::NDC::push(modName + "-stop");   	
}

//void ArmMover::showState()
//{
//    switch (getState())
//    {
//        case eSTATE_ACCEL:
//            LOG4CXX_INFO(logger, ">> accel");
//            log4cxx::NDC::pop();	          
//            log4cxx::NDC::push(modName + "-accel");   	
//            break;
//            
//        case eSTATE_BRAKE:
//            LOG4CXX_INFO(logger, ">> brake");
//            log4cxx::NDC::pop();	          
//            log4cxx::NDC::push(modName + "-brake");   	
//            break;
//                    
//        case eSTATE_KEEP:
//            LOG4CXX_INFO(logger, ">> keep");
//            log4cxx::NDC::pop();	          
//            log4cxx::NDC::push(modName + "-keep");   	
//            break;
//            
//        case eSTATE_STOP:
//            LOG4CXX_INFO(logger, ">> stop");
//            log4cxx::NDC::pop();	          
//            log4cxx::NDC::push(modName + "-stop");   	
//            break;
//    }   // end switch    
//}

}