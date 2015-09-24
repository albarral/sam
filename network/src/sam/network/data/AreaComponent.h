#ifndef __SAM_NETWORK_AREACOMPONENT_H
#define __SAM_NETWORK_AREACOMPONENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
namespace network
{
// Model class for network's area components 
class AreaComponent
{
public:
    enum eType
    {
        eTYPE_MODULE,
        eTYPE_ACTION,
        eTYPE_SENSOR
    };
    static const std::string moduleType;
    static const std::string actionType;
    static const std::string sensorType;
    
private:
    int ID;                             // item ID
    std::string type;             // item type (action or sensor)
    std::string name;             // item name
    //std::string description;    // item description

public:    
    AreaComponent(int ID, int type, std::string name);
    ~AreaComponent();

    int getID() {return ID;};
    bool isModule() {return (type.compare(moduleType) == 0);};
    bool isAction() {return (type.compare(actionType) == 0);};
    bool isSensor() {return (type.compare(sensorType) == 0);};
    std::string getName() {return name;};
    //std::string getDescription() {return description;};
};

}
}
#endif
