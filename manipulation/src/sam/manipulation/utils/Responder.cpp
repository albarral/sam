/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Responder.h"

using namespace log4cxx;

namespace sam
{
LoggerPtr Responder::logger(Logger::getLogger("sam.responder"));

// Constructor 
Responder::Responder ()
{
    reset();
}

// Destructor
Responder::~Responder ()
{
}

void Responder::reset()
{
    command = "";
    iCommand = Responder::INVALID_WORD;
    brequested = false;    
}

void Responder::addWord(std::string command)
{
    listWords.push_back(command);    
}

void Responder::listen()
{
    reset();
    
    LOG4CXX_INFO(logger, "> ?");
    std::string buffer;        
    std::getline(std::cin, buffer);
    brequested = true;    
        
    // check if the input is a valid command
    if (!buffer.empty())
    {        
        command = buffer;
        std::vector<std::string>::iterator it_word = listWords.begin();
        int pos = 0;

        while (it_word != listWords.end())
        {
            // if command is a valid one, finish checking
            if (buffer.compare(*it_word) == 0) 
            {
                command = *it_word;
                iCommand = pos;                
                break;
            }
            it_word++;
            pos++;
        }        
    }    
}


void Responder::showAcceptedWords()
{
    LOG4CXX_INFO(logger, "Responder accepted words:");
    
    std::vector<std::string>::iterator it_word = listWords.begin();

    while (it_word != listWords.end())
    {
        LOG4CXX_INFO(logger, *it_word);
             
        it_word++;
    }
}

void Responder::clearWords()
{
    listWords.clear();
}

}