#ifndef __T3PLAYER_BUS_H
#define __T3PLAYER_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/3tplayer/shared/Config.h"
#include "sam/3tplayer/shared/Connections.h"
#include "sam/3tplayer/shared/Data.h"

namespace sam 
{
namespace t3player 
{
// The Bus holds everything that needs to be shared by the different modules (each running its own thread).
class Bus
{
    private:
        Config oConfig;
        Connections oConnections;
        Data oData;

    public:
        Bus();
        ~Bus();

        Config& getConfig() {return oConfig;};
        Connections& getConnections() {return oConnections;};
        Data& getData() {return oData;};
};

}
}    
#endif
