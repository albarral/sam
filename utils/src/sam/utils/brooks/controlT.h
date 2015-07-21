#ifndef __GOON_CONTROLT_H
#define __GOON_CONTROLT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "control.h"

namespace goon 
{
// This class implements a Brooks control command.
// It works as the base Control class, but it additionaly stores the input parameter on command request & returns it on command state check.
// Thread safety implemented.
template <typename T>
class ControlT : public Control
{
    protected:
        T value;
        std::mutex mutex2;

    public:
        ControlT();
        //~ControlT();
        
        // Requests the execution of the control command, with a specified input parameter.
        void request (T& value);
                
        // Checks if a command request is pending to be executed, giving access to the stored input parameter.
        // After the check, the request is considered not pending anymore.
        virtual bool checkRequested (T& value);
        
        // just gets the last requested value
        void getValue (T& value);
};

// note: DEFINITIONS OF TEMPLATE CLASSES MUST BE PLACED IN HEADER

// Constructor
template <typename T>
ControlT<T>::ControlT()
{        
}
    
template <typename T>
void ControlT<T>::request(T& value)
{  
    std::lock_guard<std::mutex> locker(mutex2);

    this->value = value;    
    Control::request();
}

template <typename T>
bool ControlT<T>::checkRequested(T& value)
{
    std::lock_guard<std::mutex> locker(mutex2);
    
    if (Control::checkRequested())
    {
        value = this->value;
        return true;
    }
    else
        return false;
}

template <typename T>
void ControlT<T>::getValue(T& value)
{
    std::lock_guard<std::mutex> locker(mutex2);
    
    value = this->value;
}

}    
#endif
