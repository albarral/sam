#ifndef __T3PLAYER_PLAY_H
#define __T3PLAYER_PLAY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include "sam/3tplayer/Bus.h"
#include "sam/3tplayer/core/Players.h"
#include "sam/3tplayer/data/structs.h"
#include "goon/utils/module.h"
#include "goon/utils/Click.h"

namespace sam 
{
namespace t3player 
{
// The Play module is responsible for the whole game flow (game start, turns control, game over and troubles).
class Play : public goon::Module
{    
private:
    static log4cxx::LoggerPtr logger;
    Config& mConfig;
    Connections& mConnections;
    Data& mData;    
    int loop_ms;             // loop period 
    
    Players oPlayers;
    goon::Click oClickAgent;     // used to measure agent delays
    goon::Click oClickPlayer;    // used to measure player delays
    
    // States of the Play module (7))
    enum eState
    {
         eGAME_OFF,
         eGAME_START,            // init game 
         eGAME_AGENT,           // agent's turn 
         eGAME_MOVE,           // agent's move 
         eGAME_PLAYER,          // opponent's turn
         eGAME_CHECK,          // check board changes
         eGAME_END,                // game finished
         eGAME_TROUBLE            // invalid game situation
    };
    
public:
    Play(Bus& oBus);
    ~Play();

    // ask the module to stop
    void stop();               
    
protected:
    // runs the thread
    void run();

private:    
    // executes the module's loop
    void loop ();
            
    // sets the game players
    void setPlayers();
    // sets the first turn
    void setFirstTurn();    
    // checks if it's the agent's turn
    bool isMyTurn();    
    
    Cell& selectNextMove();
    bool checkBoardChanged();
    bool checkGameOver();
    
    // actions done on each state change
    void changeState(int nextState);
};
}    
}
#endif
