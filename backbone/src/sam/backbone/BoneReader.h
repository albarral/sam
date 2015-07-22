#ifndef __SAM_BACKBONE_BONELISTEN_H
#define __SAM_BACKBONE_BONELISTEN_H

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
    std::string select;     // query for selecting new messages
    
public:
    BoneReader();
                    
    // Tunes reader/writer to table & area
    virtual void tune(std::string tabMessages, std::string area);  
    // Reads new messages from table
    void readMessages();
    
    // Jumps to next message in the list. Returns false when end of list reached.
    bool nextMessage();
    // Gets pointed message
    BoneMsg* getMessage() {return pBoneMsg;};
    
    // Marks DB message of specified module as processed ok
    void markMessageOk(int areaID, int moduleID);
    // Marks DB message of specified module as unknown
    void markMessageUnknown(int areaID, int moduleID);
    
};
}

#endif
