#ifndef __T3PLAYER_FIELD_H
#define __T3PLAYER_FIELD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/3tplayer/Bus.h"
#include "goon/utils/module.h"

#include "sam/test/VirtualBoard.h"

namespace sam 
{
namespace t3player 
{
// The Field module is responsible for monitoring the state of the board and detecting changes on it.
class Field : public goon::Module
{    
private:
    static log4cxx::LoggerPtr logger;
    Config& mConfig;
    Connections& mConnections;
    Data& mData;
    
    int loop_ms;    // loop period (slow or fast)

    // for testing
    sam::VirtualBoard* mVirBoard;
    
    // States of the Field module
    enum eState
    {
         eFIELD_OFF,
         eFIELD_STATIC,         // no changes in the field
         eFIELD_CHANGING,   // something is being changed
         eFIELD_CHANGED     // change has finished
    };
    
public:
    Field(Bus& oBus);
    ~Field();

    // ask the module to stop
    void stop();               
    // for testing
    void setVirtualBoard(sam::VirtualBoard* oVirBoard) {mVirBoard = oVirBoard;};
    
protected:
    // runs the thread
    void run();

private:    
    // executes the module's loop
    void loop ();
    
    // checks if the board state has changed
    bool checkBoardChanged();
    
    // actions done on each state change
    void changeState(int nextState);
    void goFast();
    void goSlow();
};
}    
}
#endif
