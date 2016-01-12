#ifndef __SAM_HEAD_IPCAMHEAD_H
#define __SAM_HEAD_IPCAMHEAD_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <curl/curl.h>
#include <log4cxx/logger.h>

#include "sam/head/modules/Head.h"

namespace sam 
{
namespace head
{    
// This class controls the pan/tilt position of an IP camera.
// It derives from Head.
class IPCamHead : public Head
{
private:
    static log4cxx::LoggerPtr logger;
    int port;
    CURL* curl;
    static bool bcurlActive;

public:
    IPCamHead (std::string address, int port);
    ~IPCamHead();

    // connects to the camera 
    virtual int connect();
    virtual int disconnect();

    // move head to specified position
    virtual int move(int pan, int tilt);
    
private:
    static void activateCurl();
    static void deactivateCurl();
    // checks that pan and tilt lay inside the limits, cutting them if necessary.  
    void checkLimits();

};

}
}	
#endif
	
