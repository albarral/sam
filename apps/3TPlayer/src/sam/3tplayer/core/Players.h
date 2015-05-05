#ifndef __T3PLAYER_PLAYERS_H
#define __T3PLAYER_PLAYERS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "sam/3tplayer/data/Player.h"

namespace sam 
{
namespace t3player 
{
// This class manages the players & turns in the game
class Players 
{    
private:
    static log4cxx::LoggerPtr logger;
    std::vector<Player> listPlayers;    
    int turn;
    
public:
    Players();
    ~Players();

    // clears the list of players
    void reset();
    // adds a new opponent player
    void addPlayer();
    // adds the agent player
    void addMe();
    // shows all players & their figures
    void showPlayersData();
    
    // gives the turn to the specified player
    void giveTurn(int playerID);
    // checks if turn was given
    bool isTurnGiven() {return (turn != -1);}
    // changes turn to next player
    void nextTurn();
    // gets the player who has the turn now
    Player& whoPlays();    
};

}    
}
#endif
