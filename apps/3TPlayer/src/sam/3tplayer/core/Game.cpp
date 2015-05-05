/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Game.h"

using namespace log4cxx;

namespace sam 
{
namespace t3player 
{
LoggerPtr Game::logger(Logger::getLogger("sam.t3player.game"));

// Constructor
Game::Game ()
{
}

// Destructor
Game::~Game ()
{
}

void Game::reset()
{    
    result = eRES_NOTHING;
    bRow = bCol = bDiagonal = bHoles = false;
}

void Game::checkBoard(cv::Mat matBoard, int cellState)
{
    reset();
    
    checkRows(matBoard, cellState);
    if (bRow)
    {
        result = eRES_WINNER;
        return;
    }
        
    checkColumns(matBoard, cellState);
    if (bCol)
    {
        result = eRES_WINNER;
        return;
    }
    
    checkDiagonal1(matBoard, cellState);
    if (bDiagonal)
    {
        result = eRES_WINNER;
        return;
    }

    checkDiagonal2(matBoard, cellState);    
    if (bDiagonal)
    {
        result = eRES_WINNER;
        return;
    }

    checkHoles(matBoard);
       
    // if no holes, draw
    if (!bHoles)
        result = eRES_DRAW;
    // else, nothing
    else
        result = eRES_NOTHING;
}
   
void Game::checkRows(cv::Mat matBoard, int cellState)
{
    bool bcomplete;

    // for each row
    for (int i=0; i<matBoard.rows; i++)
    {
        bcomplete = true;
        int* matRow = matBoard.ptr<int>(i);
        // traverse columns
        for (int j=0; j<matBoard.cols; j++)
        {
            // if different cell, incomplete row
            if (matRow[j] != cellState)  
            {
                bcomplete = false;
                break;   // go for next row
            }
        }
        // if row complete, end check
        if (bcomplete)
        {
            LOG4CXX_INFO(logger, "3 found in row" << i);
            bRow = true;
            break;
        }
    }                                                                       
}

void Game::checkColumns(cv::Mat matBoard, int cellState)
{
    bool bcomplete;

    // for each column
    for (int j=0; j<matBoard.cols; j++)
    {
        bcomplete = true;
        // traverse rows
        for (int i=0; i<matBoard.rows; i++)
        {
            // if different cell, incomplete col
            if (matBoard.at<int>(i,j) != cellState)  
            {
                bcomplete = false;
                break;  // go for next col
            }
        }
        // if col complete, end check
        if (bcomplete)
        {
            LOG4CXX_INFO(logger, "3 found in col" << j);
            bCol = true;
            break;
        }
    }                                                                       
}
  
void Game::checkDiagonal1(cv::Mat matBoard, int cellState)
{
    bool bcomplete = true;

    // walk diagonal
    for (int k=0; k<matBoard.rows; k++)
    {
        // if different cell, incomplete diagonal
        if (matBoard.at<int>(k,k) != cellState)  
        {
            bcomplete = false;
            break;  
        }
    }
    // if diag complete
    if (bcomplete)
    {
        bDiagonal = true;
        LOG4CXX_INFO(logger, "3 line in diagonal 1");
    }                                                                           
}

void Game::checkDiagonal2(cv::Mat matBoard, int cellState)
{
    bool bcomplete = true;
    int maxCol = matBoard.cols - 1;

    // walk diagonal
    for (int i=0; i<matBoard.rows; i++)
    {
        int j = maxCol - i;
        // if different cell, incomplete diagonal
        if (matBoard.at<int>(i,j) != cellState)  
        {
            bcomplete = false;
            break;  
        }
    }
    // if diag complete
    if (bcomplete)
    {
        bDiagonal = true;
        LOG4CXX_INFO(logger, "3 line in diagonal 2");
    }                                                                           
}

void Game::checkHoles(cv::Mat matBoard)
{
    // for each row
    for (int i=0; i<matBoard.rows; i++)
    {
        int* matRow = matBoard.ptr<int>(i);
        // traverse columns
        for (int j=0; j<matBoard.cols; j++)
        {
            // if hole found, end check
            if (matRow[j] == eCELL_FREE)  
            {
                LOG4CXX_INFO(logger, "hole found in row" << i);
                bHoles = true;
                return; 
            }
        }
    }                                                                       
}

}
}
