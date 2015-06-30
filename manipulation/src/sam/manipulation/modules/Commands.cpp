/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "Commands.h"

namespace sam
{
namespace manipulation
{

// Constructor 
//ComsManip::ComsManip ()
//{    
// }

// Destructor
//ComsManip::~ComsManip ()
//{
//}

 // check if command contains "mov"
bool Commands::isArmMoverCommand(std::string command)
{
    bool bMoverCommand = (command.find("mov") != std::string::npos);
    
    return bMoverCommand;
};

}
}