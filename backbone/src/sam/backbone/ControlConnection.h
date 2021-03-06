#ifndef __SAM_BACKBONE_CONTROLCONNECTION_H
#define __SAM_BACKBONE_CONTROLCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BaseConnection.h"
#include "sam/network/data/ControlMsg.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading & writing messages to a backbone CONTROL table
// Extends from BaseConnection    
class ControlConnection : public BaseConnection
{
private:        
    bool btuned;                        // flag to indicate the target table is set
    std::string tabMessages;      // name of CONTROL table
    // logic
    std::vector<network::ControlMsg> listMessages;    // unprocessed messages list
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
    bool writeMessage(network::ControlMsg& oControlMsg);
    // Returns the list of read control messages
    std::vector<network::ControlMsg>& getListMessages() {return listMessages;}

    
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
