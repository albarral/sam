#ifndef __SAM_NETWORK_NETPRIORITY_H
#define __SAM_NETWORK_NETPRIORITY_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace sam 
{
namespace network
{    
// Control priorities for networked modules
class ControlPriority
{
    public:       
        // head control priorities ...
        static const int headPriority4Tracker = 1;      // for Tracker module (Look area)
        static const int headPriority4Focus = 2;        // for Focus module (Look area)
        static const int headPriority4User = 5;         // for external user control (Alive area)
        
    public:
        //ControlPriority();
        
};

}
}    
#endif
