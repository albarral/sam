#ifndef __SAM_BACKBONE_BONEMSG_H
#define __SAM_BACKBONE_BONEMSG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
// Bean for TAB_CONTROL & TAB_SENSE
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
    int area;                  // ID of target area 
    int module;              // ID of target module 
    int info;                   // ID of control or sense symbol (the message info or command)
    int detail;                 // detail of the control or sense message (optional)
    int processed;          // processed state (one of eProc values)

public:    
    BoneMsg(int area, int module, int info, int detail, int processed = eMSG_NEW);
    ~BoneMsg();

    int getArea() {return area;};
    int getModule() {return module;};
    int getInfo() {return info;};    
    int getDetail() {return detail;};
    int getProcessed() {return processed;}
    
    // creates string with all data (for logging purpose)
    std::string toString();
};
}
#endif
