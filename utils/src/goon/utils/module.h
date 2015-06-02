#ifndef __GOON_MODULE_H
#define __GOON_MODULE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <thread>
#include <mutex>

namespace goon 
{
// Base class designed to run a module inside its own thread.
// Method to be implemented in the derived class: run().    
// Methods to start & stop the module:
// - launch() -> starts the module.
// - stop()    -> asks the module to stop.
// - wait()    -> waits till the thread is finished.
// Thread safety implemented.    
class Module 
{
    protected:
        std::mutex mutex;
        std::thread t;        // module's thread       
        bool bactive;         // indicates that the thread is active & running  
        bool bstop;          // indicates a stop request has been received 
        int state;             // module's present state
        int prevState;      // module's previous state
        int tics;               // number of loops the module has been executed

    public:
        Module();
        //~Module();
        
        // launchs the thread
        void launch();                
        // asks the thread to stop
        virtual void stop();        
        // waits till the thread is finished
        void wait();

        // checks the module activity
        bool isActive();
        // checks the module state
        int getState();
        // checks the module previous state
        int getPrevState();
        // gets the number of tics
        int getTics();
                
    protected:
        // main while running in the thread 
        virtual void run() = 0;
        // loop of the running thread (by default increases the number of tics)
        virtual void loop();
        // checks if stop was requested
        bool stopRequested();        
                
        // sets the activation flag
        void setActive(bool bvalue);
        // sets a new state
        void setState(int state);
};
}    
#endif
