#ifndef __VIRTUAL_BOARD_H
#define __VIRTUAL_BOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

namespace sam 
{
// Represents a virtual tic-tac-toe board (used for testing)
class VirtualBoard
{
private:
        static log4cxx::LoggerPtr logger;
        cv::Mat matrix;     // 3x3 matrix simulating the board
        bool bFull;     // all cells filled

public:
    // States of the board's cells
    enum eCell
    {
         eCELL_FREE,               // cell not occupied
         eCELL_AGENT,           // cell occupied by agent
         eCELL_PLAYER,          // cell occupied by human player
    };

        VirtualBoard();
        ~VirtualBoard();

        void reset();   
        cv::Mat& getMatrix() {return matrix;};
        bool selectCell (int row, int col);
        bool simulatePlayer();
        bool isFull() {return bFull;};
        // void showBoard();
};

}
#endif
