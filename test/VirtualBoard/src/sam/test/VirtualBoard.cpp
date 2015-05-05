/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "VirtualBoard.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr VirtualBoard::logger(Logger::getLogger("sam.virtualboard"));

VirtualBoard::VirtualBoard ()
{
    reset();
}

VirtualBoard::~VirtualBoard()
{
}

void VirtualBoard::reset()  
{
    matrix = cv::Mat::zeros(3, 3, CV_8UC1);
    bFull = false;
};

// selects the given cell for the agent
bool VirtualBoard::selectCell(int row, int col)
{
    if (row < 0 || row > 2 || col < 0 || col > 2 )
    {
        LOG4CXX_WARN(logger, "invalid cell selected: " << row << ", " << col);
        return false;
    }
        
    int state = matrix.at<uchar>(row,col);
    
    if (state == eCELL_FREE)
    {
        matrix.at<uchar>(row,col) = (uchar)eCELL_AGENT;
        LOG4CXX_INFO(logger, "agent cell: " << row << ", " << col);
        return true;
    }
    else 
    {
        LOG4CXX_WARN(logger, "cell not empty: " << row << ", " << col);
        return true;
    }
}

// selects a free cell for the player (the first available)
bool VirtualBoard::simulatePlayer()
{
    for (int i = 0; i < matrix.rows; i++)
    for (int j = 0; j < matrix.cols; j++)
    {
        if (matrix.at<uchar>(i,j) == eCELL_FREE)
        {
            matrix.at<uchar>(i,j) = (uchar)eCELL_PLAYER;
            LOG4CXX_INFO(logger, "player cell: " << i << ", " << j);
            return true;            
        }
    }
    
    bFull = true;    
    LOG4CXX_WARN(logger, "board is full");
    return false;
}

}