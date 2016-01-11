/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "ArmTranslator.h"
#include "sam/network/data/NetworkCode.h"

namespace sam
{
namespace network
{     
// Constructor 
ArmTranslator::ArmTranslator ()
{           
    benabled = false;
}

void ArmTranslator::init(std::vector<NetworkCode>& listNetworkCodes)
{
    buildMap(listNetworkCodes);
     
    setAreaModules();
    setAreaActions();
    setAreaSensors();
 
    benabled = true;
}

void ArmTranslator::buildMap(std::vector<NetworkCode>& listNetworkCodes)
{
    // first clear the translation map
    mapCodes.clear();

    // then fill the map
    for (auto& element: listNetworkCodes)
    {
        mapCodes.emplace(element.getName(), element.getID());
    }        
}

int ArmTranslator::findMapCode(std::string codeName)
{
    try
    {
        return mapCodes.at(codeName);
    }
    catch (const std::out_of_range& oor) 
    {
        return ArmTranslator::UNKNOWN_CODE;
    }
}

void ArmTranslator::setAreaModules()
{
    moduleJMOVER_1 = findMapCode("JMOVER_1");
    moduleJMOVER_2 = findMapCode("JMOVER_2");
    moduleJMOVER_3 = findMapCode("JMOVER_3");
    moduleJMOVER_4 = findMapCode("JMOVER_4");
    moduleJCONTROL_1 = findMapCode("JCONTROL_1");
    moduleJCONTROL_2 = findMapCode("JCONTROL_2");
    moduleJCONTROL_3 = findMapCode("JCONTROL_3");
    moduleJCONTROL_4 = findMapCode("JCONTROL_4");
    moduleJANGLE_1 = findMapCode("JANGLE_1");
    moduleJANGLE_2 = findMapCode("JANGLE_2");
    moduleJANGLE_3 = findMapCode("JANGLE_3");
    moduleJANGLE_4 = findMapCode("JANGLE_4");                
}

void ArmTranslator::setAreaActions()
{
    actionSTART = findMapCode("START");
    actionSTOP = findMapCode("STOP");
    actionJCONTROL_SPEED = findMapCode("JCONTROL_SPEED");
    actionJMOVER_UP = findMapCode("JMOVER_UP");
    actionJMOVER_DOWN = findMapCode("JMOVER_DOWN");
    actionJMOVER_KEEP = findMapCode("JMOVER_KEEP");
    actionJMOVER_BRAKE = findMapCode("JMOVER_BRAKE");
    actionJMOVER_STOP = findMapCode("JMOVER_STOP");    
}

void ArmTranslator::setAreaSensors()
{
    senseJANGLE_IST_ANGLE = findMapCode("JANGLE_IST_ANGLE"); 
    senseJCONTROL_IST_SPEED = findMapCode("JCONTROL_IST_SPEED"); 
    senseJCONTROL_STATE = findMapCode("JCONTROL_STATE"); 
    senseJCONTROL_LIMIT_REACHED = findMapCode("JCONTROL_LIMIT_REACHED"); 
    senseJMOVER_STATE = findMapCode("JMOVER_STATE"); 
}

}
}