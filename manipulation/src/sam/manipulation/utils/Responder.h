#ifndef __SAM_RESPONDER_H
#define __SAM_RESPONDER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

namespace sam 
{
// Auxiliary class for interface communication through the console input.
class Responder
{
public:
    static const int INVALID_WORD = -1;    

private:
    std::vector<std::string> listWords;        // list of accepted words 
    bool brequested;                                // indicates a command has been requested
    std::string command;                          // requested command (null if not valid)      
    int commandID;                                  // ID of requested command (0 if not valid)   

public:
    Responder ();
    ~Responder();

    // add a new command to rgw rhw 
    void addWord(std::string command);
    
    // analyzes the commands requested through the console
    void listen();
    
    // checks if a command has been requested
    bool isCommandRequested() {return brequested;};    
    std::string& getCommandString() {return command;};
    int getCommandID() {return commandID;};

    // return list of accepted words
    std::vector<std::string>& getListWords() {return listWords;};
    
    // reset list of accepted words
    void clearWords();
    
private:
    // resets Responder state
    void reset();
    
};
}		
#endif
