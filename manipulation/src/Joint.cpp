/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Joint.h"

namespace sam 
{
namespace t3player 
{
Joint::Joint ()
{
    enabled = false;
}

Joint::~Joint()
{
}

void Joint::init(int type, int length, int limit1, int limit2)
{
    if (type < 0 || 
            type >= eJOINT_INVALID || 
            length < 0 ||
            limit1 >= limit2)
        return;

    this->type = type;
    this->length = length;
    this->limit1 = limit1;
    this->limit2 = limit2;
    enabled = true;
};

// updates matNow and checks differences with matPrev
void Joint::update(cv::Mat& mat)
{
    std::lock_guard<std::mutex> locker(mutex);

    matNow = mat.clone();
    cv::Mat matChanges = matNow - matPrev;    
    matPrev = matNow;
    numChanges = cv::countNonZero(matChanges);           
};

bool Joint::isChanged() 
{
    std::lock_guard<std::mutex> locker(mutex);
    
    return (numChanges > 0);
};

cv::Mat& Joint::getMatNowCopy()
{
    std::lock_guard<std::mutex> locker(mutex);
    
    cv::Mat matCopy = matNow.clone();    
    return matCopy;
}
}
}
