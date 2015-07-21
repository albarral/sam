#ifndef __GOON_SUPPRESS_CONTROL_H
#define __GOON_SUPPRESS_CONTROL_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "control.h"

namespace goon 
{
// This class implements the suppression mechanism on control commands, as defined in Brooks subsumption architecture.
// Command requests are received from different sources with different priorities, but only the one with highest priority is finally executed.
// The active priority gets updated only if the priority of the incoming request is higher.
// To reset the active priority the clearPriority() call must be used.
// It derives from the base Control class.
// Thread safety implemented.
class SuppressControl : public Control
{
    private:
        int priority;           // active priority (highest of received requests)
        std::mutex mutex2;

    public:
        SuppressControl();
        //~SuppressControl();
        
        // Requests the execution of the control command with a given priority value.
        // The request will only be accepted if the specified priority > the active one for this command.
        void request (int priority);
                
       // Checks if a command request is pending to be executed.
       // After the check, the request is considered not pending anymore.
       // The priority is also cleared after the ckeck.
       virtual bool checkRequested();
        
    private:
        // Checks if the new request priority is higher than the active one.
        // If so it updates it with the new value, and returns true. Otherwise, false is returned.
        bool checkPriority(int priority);

        // Sets the priority back to 0 .
        void clearPriority();       
};
}    
#endif
