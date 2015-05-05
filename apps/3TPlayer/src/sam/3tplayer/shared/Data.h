#ifndef __T3PLAYER_DATA_H
#define __T3PLAYER_DATA_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "sam/3tplayer/data/Board.h"

namespace sam 
{
namespace t3player 
{
class Data
{
    private:
        Board oBoard;        
        
    public:
        Data();
        ~Data();                

        Board& getBoard() {return oBoard;}
};
}
}    
#endif
