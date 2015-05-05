#ifndef __T3PLAYER_GAME_H
#define __T3PLAYER_GAME_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

namespace sam 
{
namespace t3player 
{
// Manages the internals of the TicTacToe game, with their situations & results
class Game
{
private:
    static log4cxx::LoggerPtr logger;
    int result;     // one of eResult
    bool bRow;  
    bool bCol;
    bool bDiagonal;
    bool bHoles;

public:
    // State of the board's cells
    enum eState
    {
         eCELL_FREE,               // cell not occupied
         eCELL_MINE,              // cell occupied by me
         eCELL_OPPONENT,    // cell occupied by opponent
         eCELL_INVALID          // none of the others
    };

    // Result of the game
    enum eResult
    {
        eRES_NOTHING,
        eRES_DRAW,              
        eRES_WINNER
    };

        Game();
        ~Game();

        // checks the board configuration for the given cell state  & obtains the corresponding game result
        void checkBoard(cv::Mat matBoard, int cellState);               
        int getResult() {return result;};
        
private:            
        void reset();
        void checkRows(cv::Mat matBoard, int cellState);
        void checkColumns(cv::Mat matBoard, int cellState);
        void checkDiagonal1(cv::Mat matBoard, int cellState);
        void checkDiagonal2(cv::Mat matBoard, int cellState);
        void checkHoles(cv::Mat matBoard);
};

}
}
#endif
