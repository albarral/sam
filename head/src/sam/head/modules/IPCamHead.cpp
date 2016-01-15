/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "sam/head/modules/IPCamHead.h"

using namespace log4cxx;

namespace sam 
{
namespace head
{    
bool IPCamHead::bcurlActive = false;

LoggerPtr IPCamHead::logger(Logger::getLogger("sam.head"));

IPCamHead::IPCamHead (std::string address, int port)
{
   this->address = address;    
   this->port = port;
   
   // activate the curl library to access head via IP commands
   activateCurl();
}

IPCamHead::~IPCamHead()
{
    // deactivate the curl library
    deactivateCurl();
}

// this must be done only once in the app
void IPCamHead::activateCurl()
{
    if (!bcurlActive)
    {
        curl_global_init(CURL_GLOBAL_ALL);
        bcurlActive = true;
    }
}

// this must be done only once in the app
void IPCamHead::deactivateCurl()
{
    if (bcurlActive)
    {
        curl_global_cleanup();
    }
}


int IPCamHead::connect() 
{       
    LOG4CXX_INFO(logger, "Connect to IP camera head ... " << address);

    if (!bconnected)
    {
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());        
        bconnected = true;
        LOG4CXX_INFO(logger, "connected");
        return 0;        
    }
    else 
    {
        LOG4CXX_ERROR(logger, "Already connected");
        return -1;        
    }
}

int IPCamHead::disconnect() 
{
    LOG4CXX_INFO(logger, "Disconnect from IP camera head ... ");

    if (bconnected)
    {
        curl_easy_cleanup(curl);
        bconnected = false;
        LOG4CXX_INFO(logger, "disconnected");
        return 0;        
    }
    else 
    {
        LOG4CXX_ERROR(logger, "Was not connected");    
        return -1;        
    }
}

// sprintf (buffer,"POST /PANTILTCONTROL.CGI HTTP/1.0\r\n
//                      Content-Type: text/plain\r\n
//                      User-Agent: user\r\n
//                      Authorization: Basic\r\n
//                      Content-Lenght: 69\r\n
//                      \r\n
//                      PanTiltHorizontal=%d&PanTiltVertical=%d&PanTiltPositionMove=true\r\n\r\n", raw_pan, raw_tilt);


// Sets the specified pan&tilt position. It returns 0 on success, -1 otherwise.
// It sends an http post with the raw pan&tilt values. 
int IPCamHead::move(int pan, int tilt)
{    
    int sentPan, sentTilt;
    CURLcode res;

    LOG4CXX_INFO(logger, "move: " << pan << ", " << tilt);

    // check pan&tilt limits
    limitedPan = pan;
    limitedTilt = tilt;
    checkLimits();
    // and obtain raw values to be sent
    sentPan = limitedPan + internalPanOffset;
    sentTilt = limitedTilt + internalTiltOffset;
    
    // build pan&tilt command
    std::string pan_command = "PanTiltHorizontal=" + std::to_string(sentPan);
    std::string tilt_command = "PanTiltVertical=" + std::to_string(sentTilt);
    std::string command = pan_command + "&" + tilt_command + "&PanTiltPositionMove=true";
    LOG4CXX_DEBUG(logger, "command: " << command);

   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command.c_str()); 
        
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        LOG4CXX_ERROR(logger, "Curl error: " << curl_easy_strerror(res));
        return -1;        
    }
    else
    {
        LOG4CXX_INFO(logger, "ok");
        return 0;        
    }
}

}
}