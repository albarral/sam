#ifndef __SAM_NETWORK_CONTROLMSG_H
#define __SAM_NETWORK_CONTROLMSG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace network
{
// Model class for network's control messages 
class ControlMsg
{
public:    
    // message processing states
     enum eProcState
    {
        eMSG_NEW,                           // new message
        eMSG_PROC_OK,                    // processed ok
        eMSG_PROC_FAILED,              // processed with errors
        eMSG_PROC_DIM
    };
         
private:
    int moduleID;              // ID of target module 
    int actionID;                // ID of control action
    int detail;                   // detail of the control action
    int priority;                // priority of the control message
    int processed;          // processed state (one of eProcState values)

public:    
    ControlMsg(int moduleID, int actionID, int detail, int priority, int processed);
    ~ControlMsg();

    int getModuleID() {return moduleID;};
    int getActionID() {return actionID;};    
    int getDetail() {return detail;};
    int getPriority() {return priority;};
    int getProcessed() {return processed;}

    int setModuleID(int value) {moduleID = value;};
    int setActionID(int value) {actionID = value;};    
    int setDetail(int value) {detail = value;};
    int setPriority(int value) {priority = value;};
    int setProcessed(int value) {processed = value;}
    
    // creates string with all data (for logging purpose)
    std::string toString();
};

}
}
#endif
