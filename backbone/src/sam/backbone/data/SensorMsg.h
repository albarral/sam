#ifndef __SAM_BACKBONE_SENSORMSG_H
#define __SAM_BACKBONE_SENSORMSG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace backbone 
{
// Bean for backbone sensor messages (stored at TAB_XXX_SENSE)
class SensorMsg
{
public:    
private:
    int moduleID;              // ID of sensed module 
    int sensorID;              // sensed info
    int detail;                   // sensed value
    int updates;               // number of times the sensor value has been updated

public:    
    SensorMsg(int moduleID, int sensorID, int detail, int updates);
    ~SensorMsg();

    int getModuleID() {return moduleID;};
    int getSensorID() {return sensorID;};    
    int getDetail() {return detail;};
    int getUpdates() {return updates;};
    
    int setModuleID(int value) {moduleID = value;};
    int setSensorID(int value) {sensorID = value;};    
    int setDetail(int value) {detail = value;};
    int setUpdates(int value) {updates = value;};

    // creates string with all data (for logging purpose)
    std::string toString();
};

}
}
#endif
