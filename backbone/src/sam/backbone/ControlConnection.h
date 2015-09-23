#ifndef __SAM_BACKBONE_CONTROLCONNECTION_H
#define __SAM_BACKBONE_CONTROLCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BoneConnection.h"
#include "data/ControlMsg.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading & writing messages to a backbone CONTROL table
// Extends from BoneConnection    
class ControlConnection : public BoneConnection
{
private:        
    bool btuned;                        // flag to indicate the target table is set
    std::string tabMessages;      // name of CONTROL table
    // logic
    std::vector<ControlMsg> listMessages;    // unprocessed messages list
    std::string select;                 // query for selecting table registers
    std::string updateOK;           // query for updating a table register
    std::string updateKO;           // query for updating a table register
    
public:
    ControlConnection();
    
    // Sets the target table name
    void tune2Table(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads new messages from table. Returns true if ok, false otherwise.
    bool readMessages();
    // Writes a new message to the table. Returns true if ok, false otherwise.
    bool writeMessage(ControlMsg& oControlMsg);
    // Returns the list of read control messages
    std::vector<ControlMsg>& getListMessages() {return listMessages;}

    
    // return the number of read messages
    int getNumReadMessages() {return listMessages.size();};
        
    // Marks DB message of specified module as processed ok
    void markMessageOk(int moduleID);
    // Marks DB message of specified module as unknown
    void markMessageFailed(int moduleID);
    
};
}
}
#endif
