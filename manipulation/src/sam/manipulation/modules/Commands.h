#ifndef __SAM_MANIP_COMMANDS_H
#define __SAM_MANIP_COMMANDS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <string>

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
         eMOVER_RIGHT,
         eMOVER_LEFT,
         eMOVER_BRAKE,
         eMOVER_KEEP,
         eMOVER_STOP,
         eMOVER_USE1,
         eMOVER_USE2,
         eMOVER_USE3,
         eMOVER_DIM
    };
    
private:
    std::vector<std::string> listCommands;
    
public:
    Commands()
    {
        // important:same order as in eCommands enum
        listCommands.push_back("r");    // move right
        listCommands.push_back("l");    // mover left
        listCommands.push_back("b");    // brake
        listCommands.push_back("k");    // keep
        listCommands.push_back("s");    // stop
        listCommands.push_back("1");    // shoulderH
        listCommands.push_back("2");    // shoulderV
        listCommands.push_back("3");    // elbow
    };
    
    std::vector<std::string>& getListCommands() {return listCommands;}    
};
}
}
#endif
