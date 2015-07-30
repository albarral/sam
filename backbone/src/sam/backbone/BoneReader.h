#ifndef __SAM_BACKBONE_BONEREADER_H
#define __SAM_BACKBONE_BONEREADER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BoneBase.h"
#include "data/BoneMsg.h"

namespace sam 
{
// Utility class for reading Backbone data. 
// Reads messages from a specific DB table & about a specific sam's area
// Extends from BoneBase class.    
class BoneReader : public BoneBase
{
private:    
    // logic
    std::vector<BoneMsg> listMessages;    // unprocessed messages list
    int index;                        // index of pointed message in the list
    BoneMsg* pBoneMsg;      // pointer to message in the list
    std::string select;            // query for selecting new messages
    std::string updateOK;       // query for updating a message state to ok
    std::string updateKO;       // query for updating a message state to failed
    
public:
    BoneReader();
                    
    // Tunes reader/writer to table & area
    virtual void tune(int direction, std::string areaName);  
    // Reads new messages from table
    void readMessages();
    
    // return the number of read messages
    int getNumReadMessages() {return listMessages.size();};
    
    // Jumps to next message in the list. Returns false when end of list reached.
    bool nextMessage();
    // Gets pointed message
    BoneMsg* getMessage() {return pBoneMsg;};
    
    // Marks DB message of specified module as processed ok
    void markMessageOk(int module);
    // Marks DB message of specified module as unknown
    void markMessageFailed(int module);
    
};
}

#endif
