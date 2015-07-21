/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Console.h"

namespace goon 
{
// asks something through the console & gets the answer    
void Console::ask(std::string question)
{
    std::cout << question << std::endl;        
    answer = "";
    std::getline(std::cin, answer);   
}

// checks if there was a filled response (other than just return)
bool Console::hasResponse()
{
    return (!answer.empty());
}
    
}