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
    static const int UNRECOGNIZED_WORD = -1;    

private:
    std::vector<std::string> listWords;        // list of accepted words 
    int numRequests;                                // number of requests received since start
    std::string command;                          // requested command (null if not valid)      
    int commandID;                                  // ID of requested command (if recognized)

public:
    Responder ();
    ~Responder();

    // add a new command to rgw rhw 
    void addWord(std::string command);
    
    // analyzes the commands requested through the console
    void listen();
    
    // checks number of command requests
    int getNumRequest() {return numRequests;};
    
    std::string& getRawCommand() {return command;};

    int getCommandID() {return commandID;};
        
    // checks if the requested command is numeric, and returns its numeric value
    bool isNumericCommand(int& numCommand);

    // return list of accepted words
    std::vector<std::string>& getListWords() {return listWords;};        
    // reset list of accepted words
    void clearWords();

private:
    // checks if last entered command is one of the recognized ones
    void checkRecognized();    
};
}		
#endif
