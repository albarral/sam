#ifndef __SAM_BACKBONE_BONECOMPONENT_H
#define __SAM_BACKBONE_BONECOMPONENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
namespace backbone 
{
// Bean for TAB_XXX_COMPONENTS    
class BoneComponent
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
    std::string description;    // item description

public:    
    BoneComponent(int ID, int type, std::string name, std::string desc);
    ~BoneComponent();

    int getID() {return ID;};
    bool isModule() {return (type.compare(moduleType) == 0);};
    bool isAction() {return (type.compare(actionType) == 0);};
    bool isSensor() {return (type.compare(sensorType) == 0);};
    std::string getName() {return name;};
    std::string getDescription() {return description;};
};

}
}
#endif
