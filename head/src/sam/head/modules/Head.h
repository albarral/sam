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
    int maxPan;                 // pan R limit
    int minPan;                  // pan L limit
    int maxTilt;                  // tilt U limit
    int minTilt;                  // tilt D limit
    int internalPanOffset;       // internal pan offset used by the camera 
    int internalTiltOffset;        // internal tilt offset used by the camera 
    int limitedPan;                    // degrees
    int limitedTilt;                     // degrees     
    bool bpanLimited;         // pan request exceeds pan range
    bool btiltLimited;           // tilt request exceeds tilt range

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

    // move head to specified position
    virtual int move(int pan, int tilt) = 0;
    // checks that pan and tilt lay inside the limits, cutting them if necessary.  
    void checkLimits();

    int getLimitedPan() {return limitedPan;};
    int getLimitedTilt() {return limitedTilt;};
    bool isPanLimited() {return bpanLimited;};
    bool isTiltLimited() {return btiltLimited;};
};

}
}	
#endif
	
