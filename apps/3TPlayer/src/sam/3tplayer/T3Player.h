#ifndef __T3PLAYER_H
#define __T3PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/3tplayer/Bus.h"
#include "sam/3tplayer/modules/Field.h"
#include "sam/test/VirtualBoard.h"

namespace sam 
{
namespace t3player 
{
// This class manages the T3Player task inside the sam system.
// It is composed of various modules, each running on its own thread.     
class T3Player
{
    private:
        static log4cxx::LoggerPtr logger;
        Bus oBus;
        Field* oField;

        // (temp) for testing
        sam::VirtualBoard* oVirBoard; 

    public:
        T3Player();
        ~T3Player();

        // starts the task's modules (each in its own )
        void startModules();
        
        // stops the tasks' modules
        void stopModules();        
};

}
}    
#endif
