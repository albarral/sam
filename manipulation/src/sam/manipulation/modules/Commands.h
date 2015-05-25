#ifndef __SAM_MANIP_COMMANDS_H
#define __SAM_MANIP_COMMANDS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace sam 
{
namespace manipulation
{
// class that holds internal commands to be user by Manipulation modules
class Commands
{
public:
    // manipulation commands
    enum eCommands
    {
         eMOVER_MOVE_R,
         eMOVER_MOVE_L,
         eMOVER_BRAKE,
         eMOVER_KEEP,
         eMOVER_STOP
    };
};
}
}
#endif
