/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "sam/utils3/Console.h"

namespace sam 
{
namespace utils
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
}