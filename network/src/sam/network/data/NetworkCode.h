#ifndef __SAM_NETWORK_NETWORKCODE_H
#define __SAM_NETWORK_NETWORKCODE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
namespace network
{
// Model class for network codes 
class NetworkCode
{
public:
    enum eType
    {
        eTYPE_MODULE,
        eTYPE_ACTION,
        eTYPE_SENSOR
    };
    static const std::string typeModule;
    static const std::string typeAction;
    static const std::string typeSensor;
    
private:
    int ID;                             // code ID
    std::string type;             // code type (action or sensor)
    std::string name;             // code name

public:    
    NetworkCode(int ID, int type, std::string name);
    ~NetworkCode();

    int getID() {return ID;};
    bool isModuleCode() {return (type.compare(typeModule) == 0);};
    bool isActionCode() {return (type.compare(typeAction) == 0);};
    bool isSensorCode() {return (type.compare(typeSensor) == 0);};
    std::string getName() {return name;};
};

}
}
#endif
