#ifndef __T3PLAYER_CONFIG_H
#define __T3PLAYER_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam 
{
namespace t3player 
{
class Config 
{
    private:        
        int slowLoop_ms;  // slow loop time for the t3player modules (in ms))
        int fastLoop_ms;  // slow loop time for the t3player modules (in ms))
        bool bvirtualMode; // game developed on a virtual board
        // Game module
        int gameDelay;  // allowed delay for game movements from agent or player (ms)
        
    public:
        Config();

        int getSlowLoopTime () {return slowLoop_ms;}
        int getFastLoopTime () {return fastLoop_ms;}
        bool isVirtualMode() {return bvirtualMode;}
        int getGameDelay() {return gameDelay;}
};

}
}    
#endif
