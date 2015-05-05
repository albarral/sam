/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "log4cxx/ndc.h"

#include "Play.h"
#include "goon/utils/Console.h"

using namespace std;
using namespace log4cxx;

namespace sam 
{
namespace t3player 
{
LoggerPtr Play::logger(Logger::getLogger("sam.t3player.game"));

// Constructor
Play::Play (Bus& oBus) : 
                mConfig(oBus.getConfig()), mConnections(oBus.getConnections()), mData(oBus.getData())
{
    Module::setState(eGAME_OFF);        
}

// Destructor
Play::~Play ()
{
}

void Play::run ()
{    
    LOG4CXX_INFO(logger, "GAME module > on");      
    loop_ms = mConfig.getSlowLoopTime();
    Module::setActive(true);      
    Module::setState(eGAME_START);

    while (!Module::stopRequested())
    {
        loop();           
        usleep(loop_ms);
    }

    Module::setState(eGAME_OFF);
    Module::setActive(false);
    LOG4CXX_INFO(logger, "GAME module > off");
}

void Play::stop()
{
    LOG4CXX_INFO(logger, "GAME module > stop requested");
    Module::stop();
}

void Play::loop ()
{    
    switch (getState())
    {            
        case eGAME_START:
            // initializes players & sets first turn 
                            
            setPlayers();
            setFirstTurn();            
            // start failed -> trouble
            if (!oPlayers.isTurnGiven())
            {
                changeState(eGAME_TROUBLE); 
            }
            // my turn -> agent
            else if (isMyTurn())
            {
                changeState(eGAME_AGENT); 
                oClickAgent.start();
            }
            // other's turn -> player
            else
            {
                changeState(eGAME_PLAYER); 
                oClickPlayer.start();
            }
            
            break;
            
        case eGAME_AGENT:
            // select next agent's movement & launch it
            
            Cell sCell = selectNextMove();            
            mConnections.getCOPickCell().request(sCell);                        
            changeState(eGAME_MOVE);            
            
            break;

        case eGAME_MOVE:
            // wait for agent's movement
            
            // if done -> check board 
            if (checkBoardChanged())
                changeState(eGAME_CHECK);            
            // if delaying too much -> trouble
            else
            {
                oClickAgent.read();
                if (oClickAgent.getMillis() > mConfig.getPlayDelay())
                    changeState(eGAME_TROUBLE);            
            }
            
            break;
            
        case eGAME_PLAYER:
            // waits for player's movement

            // if done -> check board 
            if (checkBoardChanged())
                changeState(eGAME_CHECK);            
            // if delaying too much -> trouble
            else
            {
                oClickPlayer.read();
                if (oClickPlayer.getMillis() > mConfig.getPlayDelay())
                    changeState(eGAME_TROUBLE);            
            }
            
            break;
            
        case eGAME_CHECK:
            // checks if game over situation & changes the turn if not so

            if (checkPlayOver())
                changeState(eGAME_END);
            else
            {
                oPlayers.nextTurn();

                if (isMyTurn())
                {
                    changeState(eGAME_AGENT); 
                    oClickAgent.start();
                }
                // other's turn -> player
                else
                {
                    changeState(eGAME_PLAYER); 
                    oClickPlayer.start();
                }                
            }

            break;

        case eGAME_END:

            LOG4CXX_INFO(logger, "Play over!");
            //TO DO ...
            break;
            
        case eGAME_TROUBLE:

            LOG4CXX_INFO(logger, "Play trouble!");
            //TO DO ...
            break;
    }   // end switch    
    
    Module::loop();
}

void Play::setPlayers()
{
    LOG4CXX_INFO(logger, "Ok, let's see who plays ...");
    
    oPlayers.addPlayer();
    oPlayers.addMe();
    oPlayers.showPlayersData();    
}

// Asks who will have the first turn
int Play::setFirstTurn()
{
    LOG4CXX_INFO(logger, "\nAnd let's see who moves first ...");        
    
    goon::Console oConsole;    
    bool bselected = false;
    int tries = 0;
    while (!bselected && tries<3)
    {
        // ask for the first player & give him the turn      
        oConsole.ask("Type a player number from the list above:");        
        if (oConsole.hasResponse())
        {
            try
            {
                std::string splayerID = oConsole.getAnswer();
                int playerID = std::stoi (splayerID);
                oPlayers.giveTurn(playerID);
                if (oPlayers.isTurnGiven())
                    bselected = true;
                else
                {
                    LOG4CXX_WARN(logger, "\nWrong player selection. Please, try again ...");                            
                }
            }                    
            catch (int e)
            {
              LOG4CXX_ERROR(logger, "\nTyped something but a number. Please, try again ...");        
            }
        }
        // nothing answered
        else
        {
            LOG4CXX_WARN(logger, "\nNo player selected. Please, try again ...");        
        }
        tries++;
    }            
    
    return bselected;        
}


bool Play::isMyTurn()
{
    Player oPlayer = Players.whoPlays();
    
    return (oPlayer.isMe());    
}

// Check the board & select the next move (using knowledge if possible)
Cell& Play::selectNextMove()
{    
    // TO DO ...      
    Cell sCell = {2,2};
    return sCell;    
}

// Check if the board has changed.
// For this the board changed SO is checked. If active, the ack CO is raised to inform the lower Field module.
bool Play::checkBoardChanged()
{
    if (mConnections.getSOBoardChanged().getValue() == true)
    {
        mConnections.getCOAckBoardChanged().request();
        return true;
    }
    else 
        return false;
}


// Checks if the Field module has raised the board changed flag. If so we sends him an ack to let him now we are aware.
bool Play::checkPlayOver()
{
    
    if (mConnections.getSOBoardChanged().getValue() == true)
    {
        mConnections.getCOAckBoardChanged().request();
        return true;
    }
    else 
        return false;
}


void Play::changeState(int nextState)
{
    Module::setState(nextState);
    
    log4cxx::NDC::pop();	
    switch (state) 
    {
        case eGAME_OFF:            
            LOG4CXX_DEBUG(logger, ">> off");
            log4cxx::NDC::push("off");   	
            break;
        case eGAME_START:
            LOG4CXX_INFO(logger, ">> start");
            log4cxx::NDC::push("start");   	
            break;
        case eGAME_AGENT:
            LOG4CXX_INFO(logger, ">> agent");
            log4cxx::NDC::push("agent");   	
            break;            
        case eGAME_MOVE:
            LOG4CXX_INFO(logger, ">> move");
            log4cxx::NDC::push("move");   	
            break;            
        case eGAME_PLAYER:
            LOG4CXX_INFO(logger, ">> player");
            log4cxx::NDC::push("player");   	
            break;            
        case eGAME_CHECK:
            LOG4CXX_INFO(logger, ">> check");
            log4cxx::NDC::push("check");   	
            break;            
        case eGAME_END:
            LOG4CXX_INFO(logger, ">> end");
            log4cxx::NDC::push("end");   	
            break;            
        case eGAME_TROUBLE:
            LOG4CXX_INFO(logger, ">> trouble");
            log4cxx::NDC::push("trouble");   	
            break;
    }            
}

}
}


