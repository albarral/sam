#ifndef __SAM_BACKBONE_SENSORCONNECTION_H
#define __SAM_BACKBONE_SENSORCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BaseConnection.h"
#include "sam/network/data/SensorMsg.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading & writing messages to a backbone's SENSE table
// Extends from BaseConnection        
class SensorConnection : public BaseConnection
{
private:        
    bool btuned;                        // flag to indicate the target table is set
    std::string tabMessages;           // name of SENSOR table
    // logic
    std::vector<network::SensorMsg> listMessages;    // unprocessed messages list
    std::string select;                 // query for selecting table registers
    std::string updateOK;           // query for updating a table register
    std::string updateKO;           // query for updating a table register
    
public:
    SensorConnection();
    
    // Sets the target table name
    void tune2Table(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads new messages from SENSE table. Returns true if ok, false otherwise.
    bool readMessages();
    // Writes a new message to SENSE table. Returns true if ok, false otherwise.
    bool writeMessage(network::SensorMsg& oSensorMsg);
    // Returns the list of read control messages
    std::vector<network::SensorMsg>& getListMessages() {return listMessages;}
    
    // return the number of read messages
    int getNumReadMessages() {return listMessages.size();};
};
}
}
#endif
