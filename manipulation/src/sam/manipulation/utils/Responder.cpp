/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <stdexcept>      // std::invalid_argument

#include "Responder.h"

namespace sam
{
// Constructor 
Responder::Responder ()
{
    numRequests = 0;
    command = "";    
}

// Destructor
Responder::~Responder ()
{
}

void Responder::addWord(std::string command)
{
    listWords.push_back(command);    
}

void Responder::listen()
{
    std::string buffer;        
    std::getline(std::cin, buffer);    
        
    // stores entered command & checks if it recognizes it 
    if (!buffer.empty())
    {        
        numRequests++;
        command = buffer;
        checkRecognized();
    }    
}

// Compares entered command with list of recognized words
void Responder::checkRecognized()
{
    commandID = Responder::UNRECOGNIZED_WORD;
            
    // check if the input is a valid command
    std::vector<std::string>::iterator it_word = listWords.begin();
    int pos = 0;

    while (it_word != listWords.end())
    {
        // if command is a valid one, finish checking
        if (command.compare(*it_word) == 0) 
        {
            commandID = pos;                
            break;
        }
        it_word++;
        pos++;
    }        
}


bool Responder::isNumericCommand(int& numCommand)
{
    try
    {
        numCommand = std::stoi(command);
        return true;
    }
    catch (std::invalid_argument) 
    {
        return false;        
    }
}

void Responder::clearWords()
{
    listWords.clear();
}

}