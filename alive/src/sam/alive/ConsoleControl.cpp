/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include <string>
#include <stdexcept>    

#include "sam/alive/ConsoleControl.h"

namespace sam 
{
namespace alive
{  
log4cxx::LoggerPtr ConsoleControl::logger(log4cxx::Logger::getLogger("sam.alive"));

ConsoleControl::ConsoleControl() 
{
    bQuit = false;
    mode = ConsoleControl::eMODE_UNKNOWN;
    bCmd = false;
    pan = tilt = 0;
}

ConsoleControl::~ConsoleControl() 
{
}

void ConsoleControl::init()
{
    log4cxx::NDC::push("ConsoleControl");   	    
}

void ConsoleControl::fetchCommand()
{ 
    // ask selected cell
    oConsole.ask("?");    
    std::string input= oConsole.getAnswer();
    bCmd = false;

    // chek response and skip if wrong input
    try
    {    
        // check for quit command
        if (input == "quit")
        {
            LOG4CXX_WARN(logger, "quit requested!"); 
            bQuit = true;
            return;
        }
        // check for pan mode
        if (input == "p")
        {
            LOG4CXX_INFO(logger, "pan mode"); 
            mode = ConsoleControl::eMODE_PAN;            
            return;
        }
        // check for tilt mode
        else if (input == "t")
        {
            LOG4CXX_INFO(logger, "tilt mode"); 
            mode = ConsoleControl::eMODE_TILT;            
            return;
        }
 
        // check for numeric commands
        int number = std::stoi(input);
        bCmd = true;       
        LOG4CXX_INFO(logger, "number: " << number); 
        switch (mode)
        {
            case ConsoleControl::eMODE_PAN:
                pan = number;
                break;

            case ConsoleControl::eMODE_TILT:
                tilt = number;
                break;                            
        }
    }
    catch (const std::exception& ex)
    {
        LOG4CXX_ERROR(logger, "Invalid command (wrong format) " << ex.what());
        return;
    }    
}

}
}