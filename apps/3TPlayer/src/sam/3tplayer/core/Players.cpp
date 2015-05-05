/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "Players.h"
#include "goon/utils/Console.h"

using namespace std;
using namespace log4cxx;

namespace sam 
{
namespace t3player 
{
LoggerPtr Players::logger(Logger::getLogger("sam.t3player.players"));

// Constructor
Players::Players ()
{
    reset();
}

// Destructor
Players::~Players ()
{
    reset();
}
        
// Clears the list of players
void Players::reset()
{
    listPlayers.clear();
    turn = -1;
}

// Adds a new opponent player (asking his name through console)
// Add it to the players list & to the turns control   
void Players::addPlayer()
{
    goon::Console oConsole;
    
    oConsole.ask("Player name?");
    if (oConsole.hasResponse())
    {
        std::string name = oConsole.getAnswer();
        int playerID = listPlayers.size() + 1;
        Player oPlayer(playerID, Player::ePLAYER_OPPONENT, name);        
        listPlayers.push_back(oPlayer);                
        
        LOG4CXX_INFO(logger, "New player added: " << name << " with ID " << playerID);
    }
    else
        LOG4CXX_WARN(logger, "No name was entered. No player added");    
}
        
// adds the agent player
void Players::addMe()
{
    std::string name = "Sam";
    int playerID = listPlayers.size() + 1;
    Player oPlayer(playerID, Player::ePLAYER_ME, name);
    listPlayers.push_back(oPlayer);

    LOG4CXX_INFO(logger, "Me added as player " << name << " with ID " << playerID);
}

// shows all players & its figures
void Players::showPlayersData()
{
    int games, wins, draws, looses;

    LOG4CXX_INFO(logger, ">>> Players & figures: \n");
    
    // walk the list of players
    std::vector<Player>::iterator it_player = listPlayers.begin();
    while (it_player != listPlayers.end())
    {
        LOG4CXX_INFO(logger, "player " << it_player->getID() << ": " << it_player->getName());
        
        // get tuple of figures
        std::tie(games, wins, draws, looses) = it_player->getFigures();        
        LOG4CXX_INFO(logger, "\t\t" << games << " games \t" << wins << " wins \t" << draws << " draws \t" << looses << " looses.\n");

        it_player++;	
    }    
}

// gives the turn to the specified player
void Players::giveTurn(int playerID)
{      
    // walk the list of players
    int index = 0;
    std::vector<Player>::iterator it_player = listPlayers.begin();
    while (it_player != listPlayers.end())
    {
        // if player found, give him the turn
        if (playerID == it_player->getID())
        {
            turn = index;
            
            if (it_player->isMe())
            {
                LOG4CXX_INFO(logger, "Ok, turn is for me!");
            }
            else
            {
                LOG4CXX_INFO(logger, "Ok, turn is for " << it_player->getName());            
            }
            
            break;
        }
        
        it_player++;	
        index++;
    }    
    
    if (index == listPlayers.size())    
        LOG4CXX_WARN(logger, "No player found with ID " << playerID << ". Turn was not given!");        
}

// changes turn to next player
void Players::nextTurn()
{
    turn++;
    // if last turn done, change back to first
    if (turn == listPlayers.size())
        turn = 0;
}

// gets the player who has the turn now
Player& Players::whoPlays()
{
    if (isTurnGiven())
    {
        Player oPlayer = listPlayers.at(turn);
        return oPlayer;
    }
    else
    {        
        LOG4CXX_WARN(logger, "Turn not yet assigned. Nobody plays now!");
        Player oPlayer(-1);
        return oPlayer;
    }
}

}
}


