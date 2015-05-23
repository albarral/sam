/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Config.h"

namespace sam 
{
namespace manipulation 
{
// Constructor
Config::Config ()
{    
    // TEMPORAL: should be read from a file    
    modulesFreq = 5;  // 5 Hz
    // TEMPORAL: should be read from a file    
    oShoulderHParams.set(-180, 180, 20);    
    oShoulderVParams.set(-45, 90, 20);    
    oElbowParams.set(0, 90,20);
    // TEMPORAL: should be read from a file    
    oShoulderMoverHParams.set(3, 10, 3);
    oShoulderMoverVParams.set(3, 10, 3);
    oElbowMoverParams.set(3, 10, 3);
}

}
}
