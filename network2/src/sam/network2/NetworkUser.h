#ifndef __SAM_NETWORK_NETWORKUSER_H
#define __SAM_NETWORK_NETWORKUSER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/network2/Network.h"

namespace sam 
{
namespace network
{        
// Base class to be used by users of SAM's network
class NetworkUser 
{
protected:
    bool bnetConnected;        // connected to network
    Network* pNetwork;

public:
        NetworkUser();
        //~NetworkUser();
                
       // network connection 
       void netConnect(Network* pNetwork);
       bool isNetConnected() {return bnetConnected;};
       
protected:
    Network* getNetConnection() {return pNetwork;};
};

}
}
#endif
