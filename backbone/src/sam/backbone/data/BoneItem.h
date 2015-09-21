#ifndef __SAM_BACKBONE_BONEITEM_H
#define __SAM_BACKBONE_BONEITEM_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
namespace backbone 
{
// Bean for TAB_XXX_ITEMS    
class BoneItem
{
public:
    enum eItemType
    {
        eTYPE_ACTION,
        eTYPE_SENSOR
    };
    const std::string actionType = "action";
    const std::string sensorType = "sensor";
    
private:
    int ID;                             // item ID
    std::string type;             // item type (action or sensor)
    std::string name;             // item name
    std::string description;    // item description

public:    
    BoneItem(int ID, int type, std::string name, std::string desc);
    ~BoneItem();

    int getID() {return ID;};
    bool isActionItem() {return (type.compare(actionType) == 0);};
    bool isSensorItem() {return (type.compare(sensorType) == 0);};
    std::string getName() {return name;};
    std::string getDescription() {return description;};
};

}
}
#endif
