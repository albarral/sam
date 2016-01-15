#ifndef __SAM_NETWORK_NETWORK_H
#define __SAM_NETWORK_NETWORK_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/network2/areas/HeadComs.h"

namespace sam 
{
namespace network
{    
// Network for interconnection of SAM areas
class Network
{
    private:           
        HeadComs oHeadComs;     // Head section

    public:
        Network();

        // Head section
        HeadComs& getHeadComs() {return oHeadComs;};
};

}
}    
#endif
