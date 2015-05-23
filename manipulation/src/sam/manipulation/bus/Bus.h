#ifndef __SAM_MANIPULATION_BUS_H
#define __SAM_MANIPULATION_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/manipulation/bus/Config.h"
#include "sam/manipulation/bus/Connections.h"

namespace sam 
{
namespace manipulation 
{
// The bus holds the Brooks connections between modules & the configuration data
class Bus
{
    private:
        Config oConfig;
        Connections oConnections;

    public:
        Bus();
        ~Bus();

        Config& getConfig() {return oConfig;};
        Connections& getConnections() {return oConnections;};
};

}
}    
#endif
