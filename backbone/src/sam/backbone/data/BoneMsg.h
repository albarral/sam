#ifndef __SAM_BACKBONE_BONEMSG_H
#define __SAM_BACKBONE_BONEMSG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
// Class to represent a backbone message
class BoneMsg
{
public:
    enum eProc
    {
        eMSG_NEW,                           // new message
        eMSG_PROC_OK,                    // processed ok
        eMSG_PROC_UNKNOWN,          // processed but unknown
        eMSG_PROC_DIM
    };
    
private:
    int areaID;                  // ID of area to which message belongs
    int moduleID;              // ID of module to which message belongs
    std::string info;           // message info or action
    int detail;                   // optional detail of the message
    int processed;            // processed state (one of eProc values)

public:    
    BoneMsg(int areaID, int moduleID, std::string message, int detail, int processed = eMSG_NEW);
    ~BoneMsg();

    int getAreaID() {return areaID;};
    int getModuleID() {return moduleID;};
    std::string getInfo() {return info;};    
    int getDetail() {return detail;};
    int getProcessed() {return processed;}
    
    // creates string with all data (for logging purpose)
    std::string toString();
};
}
#endif
