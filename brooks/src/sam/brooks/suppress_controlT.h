#ifndef _SAM_BROOKS_SUPPRESS_CONTROLT_H
#define _SAM_BROOKS_SUPPRESS_CONTROLT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "sam/brooks/controlT.h"

namespace sam 
{
namespace brooks
{
// This class implements the suppression mechanism on control commands with an input parameter (of any type), as defined in Brooks subsumption architecture.
// Command requests are received from different sources with different priorities, but only the one with highest priority is finally executed.
// The active priority gets updated only if the priority of the incoming request is higher.
// To reset the active priority the clearPriority() call must be used.
// It derives from the base ControlT class.
// Thread safety implemented.
template <typename T>
class SuppressControlT : public ControlT<T>
{
    private:
        int priority;           // active priority (highest of received requests)
        std::mutex mutex3;

    public:
        SuppressControlT();
        //~SuppressControlT();
        
        // Requests the execution of the control command with a specified input parameter & a given priority value.
        // The request will only be accepted if the specified priority > the active one for this command.
        void request (T& value, int priority);
                
        // Checks if a command request is pending to be executed, giving access to the stored input parameter.
        // After the check, the request is considered not pending anymore.
        // The priority is also cleared after the ckeck.
        bool checkRequested (T& value);

    private:
        // Checks if the new request priority is higher than the active one.
        // If so it updates it with the new value, and returns true. Otherwise, false is returned.
        bool checkPriority(int priority);

        // Sets the priority back to 0 .
        void clearPriority();       
};

// note: DEFINITIONS IN TEMPLATE CLASSES MUST BE PLACED IN HEADER

template <typename T>
SuppressControlT<T>::SuppressControlT ()
{    
    priority = 0;
}

template <typename T>
void SuppressControlT<T>::request(T& value, int priority)
{  
    std::lock_guard<std::mutex> locker(mutex3);

    if (checkPriority(priority))
        ControlT<T>::request(value);
}

template <typename T>
bool SuppressControlT<T>::checkRequested(T& value)
{
    std::lock_guard<std::mutex> locker(mutex3);
    
    clearPriority();    
    return ControlT<T>::checkRequested(value);
}

template <typename T>
bool SuppressControlT<T>::checkPriority(int priority)
{
    if (priority > this->priority)
    {
        this->priority = priority;
        return true;
    }
    else
        return false;
}

template <typename T>
void SuppressControlT<T>::clearPriority()
{
    priority = 0;
}

}    
}
#endif
