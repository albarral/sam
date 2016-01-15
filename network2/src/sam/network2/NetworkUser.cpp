/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/network2/NetworkUser.h"

namespace sam 
{  
namespace network
{
NetworkUser::NetworkUser()
{
    bnetConnected = false;
    pNetwork = 0;
}

void NetworkUser::netConnect(Network* pNetwork)
{
    if (pNetwork > 0)
    {
        this->pNetwork = pNetwork;
        bnetConnected = true;
    }
}

}
}