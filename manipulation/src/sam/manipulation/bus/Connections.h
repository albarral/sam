#ifndef __SAM_MANIPULATION_CONNECTIONS_H
#define __SAM_MANIPULATION_CONNECTIONS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/manipulation/bus/ConnectionSet.h"

namespace sam 
{
namespace manipulation 
{    
class Connections
{
    private:        
        ConnectionSet oShoulderConnectionsH;
        ConnectionSet oShoulderConnectionsV;
        ConnectionSet oElbowConnections;
        
    public:
        Connections();
        //~Connections();
                
        ConnectionSet& getShoulderConnectionsH() {return oShoulderConnectionsH;};
        ConnectionSet& getShoulderConnectionsV() {return oShoulderConnectionsV;};
        ConnectionSet& getElbowConnections() {return oElbowConnections;};
};

}
}    
#endif
