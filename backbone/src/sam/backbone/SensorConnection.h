#ifndef __SAM_BACKBONE_SENSORCONNECTION_H
#define __SAM_BACKBONE_SENSORCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BoneConnection.h"
#include "data/SensorMsg.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading & writing messages to a backbone SENSOR table
class SensorConnection : public BoneConnection
{
private:        
    bool btuned;                        // flag to indicate the target table is set
    std::string tabMessages;           // name of SENSOR table
    // logic
    std::vector<SensorMsg> listMessages;    // unprocessed messages list
    std::string select;                 // query for selecting table registers
    std::string updateOK;           // query for updating a table register
    std::string updateKO;           // query for updating a table register
    
public:
    SensorConnection();
    
    // Sets the target table name
    void setTabMessages(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads new messages from table
    void readMessages();
    // Writes a new message to the table
    bool writeMessage(SensorMsg& oSensorMsg);

    
    // return the number of read messages
    int getNumReadMessages() {return listMessages.size();};
};
}
}
#endif
