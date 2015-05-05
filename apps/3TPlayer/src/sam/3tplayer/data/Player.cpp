/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Player.h"

namespace sam 
{
namespace t3player 
{
Player::Player (int ID, int type, std::string name)
{
    this->ID = ID;
    this->name = name;
    
    // control entered player type 
    if (type < ePLAYER_UNKNOWN)
        this->type = type;
    else
        this->type = ePLAYER_UNKNOWN;
        
    reset();
}

Player::~Player()
{
}

void Player::reset()  
{
    numGames = numWins = numDraws = numLooses = 0;
    name = "";
};

std::tuple<int,int,int,int> Player::getFigures()
{
    std::tuple<int,int,int,int> figures = std::make_tuple (numGames, numWins, numDraws, numLooses);    
    return figures;
}

}
}
