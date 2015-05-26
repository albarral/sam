/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Responder.h"

namespace sam
{
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
    commandID = Responder::INVALID_WORD;
    brequested = false;    
}

void Responder::addWord(std::string command)
{
    listWords.push_back(command);    
}

void Responder::listen()
{
    reset();
    
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
                commandID = pos;                
                break;
            }
            it_word++;
            pos++;
        }        
    }    
}


void Responder::clearWords()
{
    listWords.clear();
}

}