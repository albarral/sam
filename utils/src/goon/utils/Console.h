#ifndef __GOON_CONSOLE_H
#define __GOON_CONSOLE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace goon 
{
class Console
{
private:
    std::string question;   // text shown in the console
    std::string answer;   // text captured from console    

public:
    Console ();
    ~Console();

    // asks something through the consode
    void ask(std::string question);
    // checks if there was a filled response (other than just return)
    bool hasResponse();
    // gets the answer captured through the console
    std::string getAnswer() {return answer;}; 
};

}		
#endif
