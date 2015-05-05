/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Board.h"

namespace sam 
{
namespace t3player 
{
Board::Board ()
{
    reset();
}

Board::~Board()
{
}

void Board::reset()  
{
    std::lock_guard<std::mutex> locker(mutex);
    
    matNow = cv::Mat::zeros(3, 3, CV_8UC1);
    matPrev = cv::Mat::zeros(3, 3, CV_8UC1);
    numChanges = 0;
};

// updates matNow and checks differences with matPrev
void Board::update(cv::Mat& mat)
{
    std::lock_guard<std::mutex> locker(mutex);

    matNow = mat.clone();
    cv::Mat matChanges = matNow - matPrev;    
    matPrev = matNow;
    numChanges = cv::countNonZero(matChanges);           
};

bool Board::isChanged() 
{
    std::lock_guard<std::mutex> locker(mutex);
    
    return (numChanges > 0);
};

cv::Mat& Board::getMatNowCopy()
{
    std::lock_guard<std::mutex> locker(mutex);
    
    cv::Mat matCopy = matNow.clone();    
    return matCopy;
}
}
}
