/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Config.h"

namespace sam 
{
namespace t3player 
{
// Constructor
Config::Config ()
{    
    // Initial values set by hand !!! They should be read from a config file (to do).
    
    slowLoop_ms = 500;  // 2 Hz
    fastLoop_ms = 200;  // 5 Hz
    bvirtualMode = true;
    gameDelay = 5000;   // 5s
}

}
}
