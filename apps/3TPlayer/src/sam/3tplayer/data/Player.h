#ifndef __T3PLAYER_PLAYER_H
#define __T3PLAYER_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <tuple> 

namespace sam 
{
namespace t3player 
{
// Holds data about a player
class Player
{
public:
    // Types of player
    enum eType
    {
         ePLAYER_ME,  
         ePLAYER_OPPONENT,
         ePLAYER_UNKNOWN
    };

private:
    int ID;       // to be used in the turn control
    int type;   // one of eTypes
    std::string name;
    int numGames;
    int numWins;
    int numDraws;
    int numLooses;
//    float level;    // level of playing performance (numWins/numGames)

public:
        Player(int ID, int type = ePLAYER_OPPONENT, std::string name = "");
        ~Player();

        int getID() {return ID;}
        bool isMe() {return (type == ePLAYER_ME);};
                    
        std::string getName() {return name;}
        
        // resets player figures
        void reset(); 
        // returns player figures (games, wins, draws & looses)
        std::tuple<int, int, int, int> getFigures();
        
        void newWin() {numGames++; numWins++;}
        void newDraw() {numGames++; numDraws++;};
        void newLoose() {numGames++; numLooses++;};        
  //      float getLevel() {return level;}
};

}
}
#endif
