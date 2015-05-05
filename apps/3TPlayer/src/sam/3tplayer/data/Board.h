#ifndef __T3PLAYER_BOARD_H
#define __T3PLAYER_BOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "opencv2/core/core.hpp"

namespace sam 
{
namespace t3player 
{
// Represents the tic tac toe board 
class Board
{
private:
        std::mutex mutex;
        cv::Mat matNow;
        cv::Mat matPrev;
        int numChanges;

public:
        Board();
        ~Board();

        // all these methods are thread protected
        void reset(); 
        void update(cv::Mat& mat); 
        bool isChanged();
        cv::Mat& getMatNowCopy();
        
private:        
        void checkChanges();        
};

}
}
#endif
