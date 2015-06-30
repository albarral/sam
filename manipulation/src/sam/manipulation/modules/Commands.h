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
         eJOINT_USE1,
         eJOINT_USE2,
         eJOINT_USE3,
         eJOINT_USE4,
         eJOINT_RIGHT,
         eJOINT_LEFT,
         eJOINT_BRAKE,
         eJOINT_KEEP,
         eJOINT_STOP,
         eARMOVER_START,
         eARMOVER_STOP,
         eFINISH_ALL,
         eJOINT_DIM
    };
    
private:
    std::vector<std::string> listCommands;
    
public:
    Commands()
    {
        // important:same order as in eCommands enum
        listCommands.push_back("j1");    // shoulderH
        listCommands.push_back("j2");    // shoulderV
        listCommands.push_back("j3");    // elbow
        listCommands.push_back("j4");    // wrist
        listCommands.push_back("r");    // joint move right
        listCommands.push_back("l");    // joint move left
        listCommands.push_back("b");    // joint brake
        listCommands.push_back("k");    // joint keep
        listCommands.push_back("s");    // joint stop
        listCommands.push_back("mov1");    // arm mover start
        listCommands.push_back("mov2");    // arm mover stop
        listCommands.push_back("off");    // arm mover stop
    };
    
    std::vector<std::string>& getListCommands() {return listCommands;}    
    
    // checks if it's an ArmMover command
    static bool isArmMoverCommand(std::string command);
};
}
}
#endif
