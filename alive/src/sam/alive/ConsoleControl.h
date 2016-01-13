#ifndef __SAM_ALIVE_CONSOLECONTROL_H
#define __SAM_ALIVE_CONSOLECONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/utils3/Console.h"

namespace sam 
{
namespace alive
{  
// Class to allow a user control the SAM agent through the console
class ConsoleControl
{
public:
    // control modes
    enum eMode
    {
        eMODE_UNKNOWN,
        eMODE_PAN,          // input data are pan commands
        eMODE_TILT           // input data are tilt commands   
    };
    
private:
    static log4cxx::LoggerPtr logger;
    utils::Console oConsole;
    bool bQuit;     // sam quit requested
    int mode;       // input mode (one of eMode's)
    bool bCmd;     // command requested
    int pan;          // commanded pan
    int tilt;            // commanded tilt
    
public:
    ConsoleControl();
    ~ConsoleControl();

    void init();
    // waits and gets a user command through the console
    void fetchCommand();

    // check if user wants to quit the game (responded "q")
    bool want2Quit() {return bQuit;};
    bool isCmdRequested() {return bCmd;};
    int getPan() {return pan;};
    int getTilt() {return tilt;};
};

}
}

#endif
