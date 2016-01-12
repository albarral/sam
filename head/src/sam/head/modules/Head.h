#ifndef __SAM_HEAD_HEAD_H 
#define __SAM_HEAD_HEAD_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace head
{    
// Base class for Head
class Head
{
protected:
    std::string address;
    bool bconnected;
    int maxPan;
    int minPan;
    int maxTilt;
    int minTilt;
    int internalPanOffset;       // internal pan offset used by the camera 
    int internalTiltOffset;        // internal tilt offset used by the camera 
    int limitedPan;                    // degrees
    int limitedTilt;                     // degrees     

public:
    Head ();
    //~Head();

    void setAddress(std::string ipAddress);
    std::string getAddress() {return address;}

    // connect to head device 
    virtual int connect() = 0;
    virtual int disconnect() = 0;

    // connects to the camera 
    bool isConnected() {return bconnected;}

    void setPanRange(int topLeft, int topRight);
    void setTiltRange(int topUp, int topDown);
    void setPanOffset(int value);
    void setTiltOffset(int value);
    
    int getMaxPan() {return maxPan;};
    int getMinPan() {return minPan;};
    int getMaxTilt() {return maxTilt;};
    int getMinTilt() {return minTilt;};
    int getLimitedPan() {return limitedPan;};
    int getLimitedTilt() {return limitedTilt;};

    // move head to specified position
    virtual int move(int pan, int tilt) = 0;
};

}
}	
#endif
	
